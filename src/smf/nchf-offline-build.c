/*
 * Copyright (C) 2019-2025 by Sukchan Lee <acetcom@gmail.com>
 * Copyright (C) 2026 by Phoenix SI (Pty) Ltd
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "nchf-offline-build.h"

/*
 * TS 32.291 Nchf_OfflineOnlyCharging API v1
 *
 * OfflineChargingDataCreate:  POST .../offlinechargingdata
 * OfflineChargingDataUpdate:  POST .../offlinechargingdata/{ref}/update
 * OfflineChargingDataRelease: POST .../offlinechargingdata/{ref}/release
 *
 * Unlike ConvergedCharging, OfflineOnlyCharging does not use
 * invocationSequenceNumber or requestedUnit.  It is a pure CDR
 * recording interface with no quota grants.
 *
 * JSON bodies are built with cJSON and attached to request->http.content
 * after ogs_sbi_build_request() sets up method/URI/service routing.
 */

/* OGS_SBI_API_V3 is defined in nchf-build.h; reuse it here */
#ifndef OGS_SBI_API_V3
#define OGS_SBI_API_V3 "v3"
#endif

/* ----------------------------------------------------------------
 * Helper: build nfConsumerIdentification JSON object
 * ---------------------------------------------------------------- */
static cJSON *build_nf_consumer_identification(void)
{
    cJSON *nf_consumer = NULL;

    nf_consumer = cJSON_CreateObject();
    if (!nf_consumer) {
        ogs_error("cJSON_CreateObject() failed [nfConsumerIdentification]");
        return NULL;
    }

    /* nodeFunctionality: "SMF" per TS 32.291 Table 6.2.3.2-1 */
    cJSON_AddStringToObject(nf_consumer, "nodeFunctionality", "SMF");

    /* nFName: local SMF NF instance UUID when available */
    if (ogs_sbi_self()->nf_instance &&
            ogs_sbi_self()->nf_instance->id) {
        cJSON_AddStringToObject(nf_consumer, "nFName",
                ogs_sbi_self()->nf_instance->id);
    }

    return nf_consumer;
}

/* ----------------------------------------------------------------
 * Helper: build pDUSessionChargingInformation JSON object
 * ---------------------------------------------------------------- */
static cJSON *build_pdu_session_charging_information(
        smf_sess_t *sess)
{
    cJSON *pdu_sess_charging = NULL;
    cJSON *pdu_sess_info = NULL;

    ogs_assert(sess);

    pdu_sess_charging = cJSON_CreateObject();
    if (!pdu_sess_charging) {
        ogs_error("cJSON_CreateObject() failed "
                "[pDUSessionChargingInformation]");
        return NULL;
    }

    /* chargingId (uint32, the 3GPP-Charging-Id) */
    if (sess->charging.id) {
        cJSON_AddNumberToObject(pdu_sess_charging,
                "chargingId", (double)sess->charging.id);
    }

    /* pduSessionInformation sub-object */
    pdu_sess_info = cJSON_CreateObject();
    if (!pdu_sess_info) {
        ogs_error("cJSON_CreateObject() failed [pduSessionInformation]");
        cJSON_Delete(pdu_sess_charging);
        return NULL;
    }
    cJSON_AddItemToObject(pdu_sess_charging,
            "pduSessionInformation", pdu_sess_info);

    /* pduSessionID */
    if (sess->psi) {
        cJSON_AddNumberToObject(pdu_sess_info,
                "pduSessionID", (double)sess->psi);
    }

    /* dnnId */
    if (sess->session.name) {
        cJSON_AddStringToObject(pdu_sess_info,
                "dnnId", sess->session.name);
    }

    /* networkSlicingInfo.sNSSAI */
    if (sess->s_nssai.sst) {
        cJSON *slicing_info = cJSON_CreateObject();
        cJSON *snssai = cJSON_CreateObject();

        if (slicing_info && snssai) {
            cJSON_AddNumberToObject(snssai, "sst",
                    (double)sess->s_nssai.sst);

            if (sess->s_nssai.sd.v != OGS_S_NSSAI_NO_SD_VALUE) {
                char *sd_string =
                    ogs_s_nssai_sd_to_string(sess->s_nssai.sd);
                if (sd_string) {
                    cJSON_AddStringToObject(snssai, "sd", sd_string);
                    ogs_free(sd_string);
                }
            }

            cJSON_AddItemToObject(slicing_info, "sNSSAI", snssai);
            cJSON_AddItemToObject(pdu_sess_info,
                    "networkSlicingInfo", slicing_info);
        } else {
            if (slicing_info) cJSON_Delete(slicing_info);
            if (snssai) cJSON_Delete(snssai);
        }
    }

    return pdu_sess_charging;
}

/* ----------------------------------------------------------------
 * Helper: build multipleUnitUsage JSON array for offline CDR
 *
 * Reports delta usage since last report.
 * Updates sess->nchf_offline.last_report snapshot after building.
 * ---------------------------------------------------------------- */
static cJSON *build_offline_multiple_unit_usage(
        smf_sess_t *sess, bool is_final)
{
    cJSON *muu_array = NULL;
    cJSON *muu_item = NULL;
    cJSON *used_unit_array = NULL;
    cJSON *used_unit = NULL;

    uint64_t delta_ul, delta_dl;
    ogs_time_t delta_duration;

    ogs_assert(sess);

    delta_ul = sess->nchf_offline.ul_octets -
        sess->nchf_offline.last_report.ul_octets;
    delta_dl = sess->nchf_offline.dl_octets -
        sess->nchf_offline.last_report.dl_octets;
    delta_duration = sess->nchf_offline.duration -
        sess->nchf_offline.last_report.duration;

    /* Nothing to report and not the final message */
    if (!is_final && !delta_ul && !delta_dl && !delta_duration)
        return NULL;

    muu_array = cJSON_CreateArray();
    if (!muu_array) {
        ogs_error("cJSON_CreateArray() failed [multipleUnitUsage]");
        return NULL;
    }

    muu_item = cJSON_CreateObject();
    if (!muu_item) {
        ogs_error("cJSON_CreateObject() failed [multipleUnitUsage item]");
        cJSON_Delete(muu_array);
        return NULL;
    }
    cJSON_AddItemToArray(muu_array, muu_item);

    /* ratingGroup: default 1 for PDU session-level charging */
    cJSON_AddNumberToObject(muu_item, "ratingGroup", 1);

    /* usedUnitContainer array */
    used_unit_array = cJSON_CreateArray();
    if (!used_unit_array) {
        ogs_error("cJSON_CreateArray() failed [usedUnitContainer]");
        cJSON_Delete(muu_array);
        return NULL;
    }
    cJSON_AddItemToObject(muu_item, "usedUnitContainer", used_unit_array);

    used_unit = cJSON_CreateObject();
    if (!used_unit) {
        ogs_error("cJSON_CreateObject() failed [usedUnitContainer item]");
        cJSON_Delete(muu_array);
        return NULL;
    }
    cJSON_AddItemToArray(used_unit_array, used_unit);

    if (delta_ul) {
        cJSON_AddNumberToObject(used_unit, "uplinkVolume",
                (double)delta_ul);
    }
    if (delta_dl) {
        cJSON_AddNumberToObject(used_unit, "downlinkVolume",
                (double)delta_dl);
    }
    if (delta_ul || delta_dl) {
        cJSON_AddNumberToObject(used_unit, "totalVolume",
                (double)(delta_ul + delta_dl));
    }
    if (delta_duration) {
        /* ogs_time_t is microseconds; TS 32.291 time is seconds */
        cJSON_AddNumberToObject(used_unit, "time",
                (double)(delta_duration / OGS_USEC_PER_SEC));
    }

    /* Snapshot current counters so next delta starts from here */
    sess->nchf_offline.last_report.ul_octets = sess->nchf_offline.ul_octets;
    sess->nchf_offline.last_report.dl_octets = sess->nchf_offline.dl_octets;
    sess->nchf_offline.last_report.duration = sess->nchf_offline.duration;

    return muu_array;
}

/* ----------------------------------------------------------------
 * Helper: attach a cJSON body to an already-built request
 * ---------------------------------------------------------------- */
static bool set_request_json_body(
        ogs_sbi_request_t *request, cJSON *body)
{
    char *content = NULL;

    ogs_assert(request);
    ogs_assert(body);

    content = cJSON_PrintUnformatted(body);
    if (!content) {
        ogs_error("cJSON_PrintUnformatted() failed");
        return false;
    }

    request->http.content = content;
    request->http.content_length = strlen(content);

    ogs_sbi_header_set(request->http.headers,
            OGS_SBI_CONTENT_TYPE, OGS_SBI_CONTENT_JSON_TYPE);

    return true;
}

/* ================================================================
 * smf_nchf_offlineonlycharging_build_create
 *
 * POST /nchf-offlineonlycharging/v3/offlinechargingdata
 *
 * Initial offline CDR session creation (TS 32.291 Section 7).
 * No multipleUnitUsage on the first request.
 * No invocationSequenceNumber (offline-only has no quota cycle).
 * ================================================================ */
ogs_sbi_request_t *smf_nchf_offlineonlycharging_build_create(
        smf_sess_t *sess, void *data)
{
    smf_ue_t *smf_ue = NULL;

    ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;

    cJSON *body = NULL;
    cJSON *nf_consumer = NULL;
    cJSON *pdu_sess_charging = NULL;
    char *timestamp = NULL;

    ogs_assert(sess);
    smf_ue = smf_ue_find_by_id(sess->smf_ue_id);
    ogs_assert(smf_ue);

    memset(&message, 0, sizeof(message));
    message.h.method = (char *)OGS_SBI_HTTP_METHOD_POST;
    message.h.service.name =
        (char *)OGS_SBI_SERVICE_NAME_NCHF_OFFLINEONLYCHARGING;
    message.h.api.version = (char *)OGS_SBI_API_V3;
    message.h.resource.component[0] =
        (char *)OGS_SBI_RESOURCE_NAME_OFFLINE_CHARGING_DATA;

    request = ogs_sbi_build_request(&message);
    if (!request) {
        ogs_error("ogs_sbi_build_request() failed");
        goto end;
    }

    /* ---- Build ChargingDataRequest JSON body ---- */

    body = cJSON_CreateObject();
    if (!body) {
        ogs_error("cJSON_CreateObject() failed [ChargingDataRequest]");
        ogs_sbi_request_free(request);
        request = NULL;
        goto end;
    }

    /* subscriberIdentifier (SUPI) */
    if (smf_ue->supi) {
        cJSON_AddStringToObject(body,
                "subscriberIdentifier", smf_ue->supi);
    }

    /* nfConsumerIdentification */
    nf_consumer = build_nf_consumer_identification();
    if (nf_consumer) {
        cJSON_AddItemToObject(body,
                "nfConsumerIdentification", nf_consumer);
    }

    /* invocationTimeStamp (RFC 3339 UTC) */
    timestamp = ogs_sbi_gmtime_string(ogs_time_now());
    if (timestamp) {
        cJSON_AddStringToObject(body,
                "invocationTimeStamp", timestamp);
        ogs_free(timestamp);
        timestamp = NULL;
    }

    /* oneTimeEvent = false (session-based, not event-based) */
    cJSON_AddBoolToObject(body, "oneTimeEvent", 0);

    /* pDUSessionChargingInformation */
    pdu_sess_charging = build_pdu_session_charging_information(sess);
    if (pdu_sess_charging) {
        cJSON_AddItemToObject(body,
                "pDUSessionChargingInformation", pdu_sess_charging);
    }

    /* No multipleUnitUsage on initial create (no usage yet) */
    /* No invocationSequenceNumber for offline-only */

    if (!set_request_json_body(request, body)) {
        ogs_error("set_request_json_body() failed");
        ogs_sbi_request_free(request);
        request = NULL;
    }

end:
    if (body)
        cJSON_Delete(body);

    return request;
}

/* ================================================================
 * smf_nchf_offlineonlycharging_build_update
 *
 * POST /nchf-offlineonlycharging/v3/offlinechargingdata/{ref}/update
 *
 * Periodic usage update: report usage delta for CDR recording.
 * No quota is requested or granted.
 * ================================================================ */
ogs_sbi_request_t *smf_nchf_offlineonlycharging_build_update(
        smf_sess_t *sess, void *data)
{
    smf_ue_t *smf_ue = NULL;

    ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;

    cJSON *body = NULL;
    cJSON *nf_consumer = NULL;
    cJSON *pdu_sess_charging = NULL;
    cJSON *muu = NULL;
    char *timestamp = NULL;

    ogs_assert(sess);
    smf_ue = smf_ue_find_by_id(sess->smf_ue_id);
    ogs_assert(smf_ue);
    ogs_assert(sess->nchf_offline_association.resource_uri);

    memset(&message, 0, sizeof(message));
    message.h.method = (char *)OGS_SBI_HTTP_METHOD_POST;
    message.h.uri = ogs_msprintf("%s/%s",
            sess->nchf_offline_association.resource_uri,
            OGS_SBI_RESOURCE_NAME_UPDATE);

    request = ogs_sbi_build_request(&message);
    if (!request) {
        ogs_error("ogs_sbi_build_request() failed");
        goto end;
    }

    /* ---- Build ChargingDataRequest JSON body ---- */

    body = cJSON_CreateObject();
    if (!body) {
        ogs_error("cJSON_CreateObject() failed [ChargingDataRequest]");
        ogs_sbi_request_free(request);
        request = NULL;
        goto end;
    }

    /* subscriberIdentifier */
    if (smf_ue->supi) {
        cJSON_AddStringToObject(body,
                "subscriberIdentifier", smf_ue->supi);
    }

    /* nfConsumerIdentification */
    nf_consumer = build_nf_consumer_identification();
    if (nf_consumer) {
        cJSON_AddItemToObject(body,
                "nfConsumerIdentification", nf_consumer);
    }

    /* invocationTimeStamp */
    timestamp = ogs_sbi_gmtime_string(ogs_time_now());
    if (timestamp) {
        cJSON_AddStringToObject(body,
                "invocationTimeStamp", timestamp);
        ogs_free(timestamp);
        timestamp = NULL;
    }

    /* multipleUnitUsage - report usage delta since last report */
    muu = build_offline_multiple_unit_usage(sess, false);
    if (muu) {
        cJSON_AddItemToObject(body, "multipleUnitUsage", muu);
    }

    /* pDUSessionChargingInformation */
    pdu_sess_charging = build_pdu_session_charging_information(sess);
    if (pdu_sess_charging) {
        cJSON_AddItemToObject(body,
                "pDUSessionChargingInformation", pdu_sess_charging);
    }

    /* No invocationSequenceNumber for offline-only */

    if (!set_request_json_body(request, body)) {
        ogs_error("set_request_json_body() failed");
        ogs_sbi_request_free(request);
        request = NULL;
    }

end:
    if (message.h.uri)
        ogs_free(message.h.uri);
    if (body)
        cJSON_Delete(body);

    return request;
}

/* ================================================================
 * smf_nchf_offlineonlycharging_build_release
 *
 * POST /nchf-offlineonlycharging/v3/offlinechargingdata/{ref}/release
 *
 * Final: report any remaining usage and close the CDR session.
 * ================================================================ */
ogs_sbi_request_t *smf_nchf_offlineonlycharging_build_release(
        smf_sess_t *sess, void *data)
{
    smf_ue_t *smf_ue = NULL;

    ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;

    cJSON *body = NULL;
    cJSON *nf_consumer = NULL;
    cJSON *pdu_sess_charging = NULL;
    cJSON *muu = NULL;
    char *timestamp = NULL;

    ogs_assert(sess);
    smf_ue = smf_ue_find_by_id(sess->smf_ue_id);
    ogs_assert(smf_ue);
    ogs_assert(sess->nchf_offline_association.resource_uri);

    memset(&message, 0, sizeof(message));
    message.h.method = (char *)OGS_SBI_HTTP_METHOD_POST;
    message.h.uri = ogs_msprintf("%s/%s",
            sess->nchf_offline_association.resource_uri,
            OGS_SBI_RESOURCE_NAME_RELEASE);

    request = ogs_sbi_build_request(&message);
    if (!request) {
        ogs_error("ogs_sbi_build_request() failed");
        goto end;
    }

    /* ---- Build ChargingDataRequest JSON body ---- */

    body = cJSON_CreateObject();
    if (!body) {
        ogs_error("cJSON_CreateObject() failed [ChargingDataRequest]");
        ogs_sbi_request_free(request);
        request = NULL;
        goto end;
    }

    /* subscriberIdentifier */
    if (smf_ue->supi) {
        cJSON_AddStringToObject(body,
                "subscriberIdentifier", smf_ue->supi);
    }

    /* nfConsumerIdentification */
    nf_consumer = build_nf_consumer_identification();
    if (nf_consumer) {
        cJSON_AddItemToObject(body,
                "nfConsumerIdentification", nf_consumer);
    }

    /* invocationTimeStamp */
    timestamp = ogs_sbi_gmtime_string(ogs_time_now());
    if (timestamp) {
        cJSON_AddStringToObject(body,
                "invocationTimeStamp", timestamp);
        ogs_free(timestamp);
        timestamp = NULL;
    }

    /* multipleUnitUsage - final usage report (is_final=true) */
    muu = build_offline_multiple_unit_usage(sess, true);
    if (muu) {
        cJSON_AddItemToObject(body, "multipleUnitUsage", muu);
    }

    /* pDUSessionChargingInformation */
    pdu_sess_charging = build_pdu_session_charging_information(sess);
    if (pdu_sess_charging) {
        cJSON_AddItemToObject(body,
                "pDUSessionChargingInformation", pdu_sess_charging);
    }

    /* No invocationSequenceNumber for offline-only */

    if (!set_request_json_body(request, body)) {
        ogs_error("set_request_json_body() failed");
        ogs_sbi_request_free(request);
        request = NULL;
    }

end:
    if (message.h.uri)
        ogs_free(message.h.uri);
    if (body)
        cJSON_Delete(body);

    return request;
}
