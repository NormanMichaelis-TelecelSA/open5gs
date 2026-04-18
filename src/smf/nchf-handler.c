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

#include "nchf-handler.h"

/*
 * TS 32.291 Nchf_ConvergedCharging response handlers
 *
 * ChargingDataCreate  → 201 Created + Location header
 * ChargingDataUpdate  → 200 OK
 * ChargingDataRelease → 204 No Content
 */

bool smf_nchf_convergedcharging_handle_create(
        smf_sess_t *sess, ogs_sbi_stream_t *stream,
        ogs_sbi_message_t *recvmsg)
{
    int rv;
    smf_ue_t *smf_ue = NULL;

    ogs_sbi_message_t message;
    ogs_sbi_header_t header;

    bool rc;
    ogs_sbi_client_t *client = NULL;
    OpenAPI_uri_scheme_e scheme = OpenAPI_uri_scheme_NULL;
    char *fqdn = NULL;
    uint16_t fqdn_port = 0;
    ogs_sockaddr_t *addr = NULL, *addr6 = NULL;

    ogs_assert(sess);
    smf_ue = smf_ue_find_by_id(sess->smf_ue_id);
    ogs_assert(smf_ue);

    ogs_assert(recvmsg);

    if (!recvmsg->http.location) {
        ogs_error("[%s:%d] No http.location in CHF Create response",
                smf_ue->supi, sess->psi);
        return false;
    }

    memset(&header, 0, sizeof(header));
    header.uri = recvmsg->http.location;

    rv = ogs_sbi_parse_header(&message, &header);
    if (rv != OGS_OK) {
        ogs_error("[%s:%d] Cannot parse CHF Location [%s]",
                smf_ue->supi, sess->psi, recvmsg->http.location);
        return false;
    }

    if (!message.h.resource.component[1]) {
        ogs_error("[%s:%d] No ChargingDataRef in Location [%s]",
                smf_ue->supi, sess->psi, recvmsg->http.location);
        ogs_sbi_header_free(&header);
        return false;
    }

    rc = ogs_sbi_getaddr_from_uri(
            &scheme, &fqdn, &fqdn_port, &addr, &addr6, header.uri);
    if (rc == false || scheme == OpenAPI_uri_scheme_NULL) {
        ogs_error("[%s:%d] Invalid CHF URI [%s]",
                smf_ue->supi, sess->psi, header.uri);
        ogs_sbi_header_free(&header);
        return false;
    }

    client = ogs_sbi_client_find(scheme, fqdn, fqdn_port, addr, addr6);
    if (!client) {
        ogs_debug("[%s:%d] ogs_sbi_client_add() for CHF",
                smf_ue->supi, sess->psi);
        client = ogs_sbi_client_add(scheme, fqdn, fqdn_port, addr, addr6);
        if (!client) {
            ogs_error("[%s:%d] ogs_sbi_client_add() failed for CHF",
                    smf_ue->supi, sess->psi);
            ogs_sbi_header_free(&header);
            ogs_free(fqdn);
            ogs_freeaddrinfo(addr);
            ogs_freeaddrinfo(addr6);
            return false;
        }
    }

    OGS_SBI_SETUP_CLIENT(&sess->nchf_association, client);

    ogs_free(fqdn);
    ogs_freeaddrinfo(addr);
    ogs_freeaddrinfo(addr6);

    CHF_CHARGING_DATA_STORE(
            sess, header.uri, message.h.resource.component[1]);

    ogs_sbi_header_free(&header);

    ogs_info("[%s:%d] CHF ChargingData created [%s]",
            smf_ue->supi, sess->psi, sess->nchf_association.id);

    return true;
}

bool smf_nchf_convergedcharging_handle_update(
        smf_sess_t *sess, ogs_sbi_stream_t *stream,
        ogs_sbi_message_t *recvmsg)
{
    smf_ue_t *smf_ue = NULL;

    ogs_assert(sess);
    smf_ue = smf_ue_find_by_id(sess->smf_ue_id);
    ogs_assert(smf_ue);
    ogs_assert(recvmsg);

    ogs_info("[%s:%d] CHF ChargingData updated [%s]",
            smf_ue->supi, sess->psi, sess->nchf_association.id);

    return true;
}

bool smf_nchf_convergedcharging_handle_release(
        smf_sess_t *sess, ogs_sbi_stream_t *stream,
        ogs_sbi_message_t *recvmsg)
{
    smf_ue_t *smf_ue = NULL;

    ogs_assert(sess);
    smf_ue = smf_ue_find_by_id(sess->smf_ue_id);
    ogs_assert(smf_ue);
    ogs_assert(recvmsg);

    ogs_info("[%s:%d] CHF ChargingData released [%s]",
            smf_ue->supi, sess->psi,
            sess->nchf_association.id ? sess->nchf_association.id : "(nil)");

    CHF_CHARGING_DATA_CLEAR(sess);

    return true;
}
