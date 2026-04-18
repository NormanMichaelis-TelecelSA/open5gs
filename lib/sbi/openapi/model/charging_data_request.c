
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "charging_data_request.h"

OpenAPI_charging_data_request_t *OpenAPI_charging_data_request_create(
    char *subscriber_identifier,
    OpenAPI_nf_identification_t *nf_consumer_identification,
    char *invocation_time_stamp,
    int invocation_sequence_number,
    bool is_retransmission_indicator,
    int retransmission_indicator,
    char *service_specification_info,
    OpenAPI_list_t *multiple_unit_usage,
    OpenAPI_list_t *triggers,
    OpenAPI_pdu_session_charging_information_t *p_du_session_charging_information,
    OpenAPI_roaming_qbc_information_t *roaming_qbc_information
)
{
    OpenAPI_charging_data_request_t *charging_data_request_local_var = ogs_malloc(sizeof(OpenAPI_charging_data_request_t));
    ogs_assert(charging_data_request_local_var);

    charging_data_request_local_var->subscriber_identifier = subscriber_identifier;
    charging_data_request_local_var->nf_consumer_identification = nf_consumer_identification;
    charging_data_request_local_var->invocation_time_stamp = invocation_time_stamp;
    charging_data_request_local_var->invocation_sequence_number = invocation_sequence_number;
    charging_data_request_local_var->is_retransmission_indicator = is_retransmission_indicator;
    charging_data_request_local_var->retransmission_indicator = retransmission_indicator;
    charging_data_request_local_var->service_specification_info = service_specification_info;
    charging_data_request_local_var->multiple_unit_usage = multiple_unit_usage;
    charging_data_request_local_var->triggers = triggers;
    charging_data_request_local_var->p_du_session_charging_information = p_du_session_charging_information;
    charging_data_request_local_var->roaming_qbc_information = roaming_qbc_information;

    return charging_data_request_local_var;
}

void OpenAPI_charging_data_request_free(OpenAPI_charging_data_request_t *charging_data_request)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == charging_data_request) {
        return;
    }
    if (charging_data_request->subscriber_identifier) {
        ogs_free(charging_data_request->subscriber_identifier);
        charging_data_request->subscriber_identifier = NULL;
    }
    if (charging_data_request->nf_consumer_identification) {
        OpenAPI_nf_identification_free(charging_data_request->nf_consumer_identification);
        charging_data_request->nf_consumer_identification = NULL;
    }
    if (charging_data_request->invocation_time_stamp) {
        ogs_free(charging_data_request->invocation_time_stamp);
        charging_data_request->invocation_time_stamp = NULL;
    }
    if (charging_data_request->service_specification_info) {
        ogs_free(charging_data_request->service_specification_info);
        charging_data_request->service_specification_info = NULL;
    }
    if (charging_data_request->multiple_unit_usage) {
        OpenAPI_list_for_each(charging_data_request->multiple_unit_usage, node) {
            OpenAPI_multiple_unit_usage_free(node->data);
        }
        OpenAPI_list_free(charging_data_request->multiple_unit_usage);
        charging_data_request->multiple_unit_usage = NULL;
    }
    if (charging_data_request->triggers) {
        OpenAPI_list_for_each(charging_data_request->triggers, node) {
            OpenAPI_trigger_free(node->data);
        }
        OpenAPI_list_free(charging_data_request->triggers);
        charging_data_request->triggers = NULL;
    }
    if (charging_data_request->p_du_session_charging_information) {
        OpenAPI_pdu_session_charging_information_free(charging_data_request->p_du_session_charging_information);
        charging_data_request->p_du_session_charging_information = NULL;
    }
    if (charging_data_request->roaming_qbc_information) {
        OpenAPI_roaming_qbc_information_free(charging_data_request->roaming_qbc_information);
        charging_data_request->roaming_qbc_information = NULL;
    }
    ogs_free(charging_data_request);
}

cJSON *OpenAPI_charging_data_request_convertToJSON(OpenAPI_charging_data_request_t *charging_data_request)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (charging_data_request == NULL) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [ChargingDataRequest]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (charging_data_request->subscriber_identifier) {
    if (cJSON_AddStringToObject(item, "subscriberIdentifier", charging_data_request->subscriber_identifier) == NULL) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [subscriber_identifier]");
        goto end;
    }
    }

    if (!charging_data_request->nf_consumer_identification) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [nf_consumer_identification]");
        return NULL;
    }
    cJSON *nf_consumer_identification_local_JSON = OpenAPI_nf_identification_convertToJSON(charging_data_request->nf_consumer_identification);
    if (nf_consumer_identification_local_JSON == NULL) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [nf_consumer_identification]");
        goto end;
    }
    cJSON_AddItemToObject(item, "nfConsumerIdentification", nf_consumer_identification_local_JSON);
    if (item->child == NULL) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [nf_consumer_identification]");
        goto end;
    }

    if (!charging_data_request->invocation_time_stamp) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [invocation_time_stamp]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "invocationTimeStamp", charging_data_request->invocation_time_stamp) == NULL) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [invocation_time_stamp]");
        goto end;
    }

    if (cJSON_AddNumberToObject(item, "invocationSequenceNumber", charging_data_request->invocation_sequence_number) == NULL) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [invocation_sequence_number]");
        goto end;
    }

    if (charging_data_request->is_retransmission_indicator) {
    if (cJSON_AddBoolToObject(item, "retransmissionIndicator", charging_data_request->retransmission_indicator) == NULL) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [retransmission_indicator]");
        goto end;
    }
    }

    if (charging_data_request->service_specification_info) {
    if (cJSON_AddStringToObject(item, "serviceSpecificationInfo", charging_data_request->service_specification_info) == NULL) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [service_specification_info]");
        goto end;
    }
    }

    if (charging_data_request->multiple_unit_usage) {
    cJSON *multiple_unit_usageList = cJSON_AddArrayToObject(item, "multipleUnitUsage");
    if (multiple_unit_usageList == NULL) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [multiple_unit_usage]");
        goto end;
    }
    OpenAPI_list_for_each(charging_data_request->multiple_unit_usage, node) {
        cJSON *itemLocal = OpenAPI_multiple_unit_usage_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [multiple_unit_usage]");
            goto end;
        }
        cJSON_AddItemToArray(multiple_unit_usageList, itemLocal);
    }
    }

    if (charging_data_request->triggers) {
    cJSON *triggersList = cJSON_AddArrayToObject(item, "triggers");
    if (triggersList == NULL) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [triggers]");
        goto end;
    }
    OpenAPI_list_for_each(charging_data_request->triggers, node) {
        cJSON *itemLocal = OpenAPI_trigger_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [triggers]");
            goto end;
        }
        cJSON_AddItemToArray(triggersList, itemLocal);
    }
    }

    if (charging_data_request->p_du_session_charging_information) {
    cJSON *p_du_session_charging_information_local_JSON = OpenAPI_pdu_session_charging_information_convertToJSON(charging_data_request->p_du_session_charging_information);
    if (p_du_session_charging_information_local_JSON == NULL) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [p_du_session_charging_information]");
        goto end;
    }
    cJSON_AddItemToObject(item, "pDUSessionChargingInformation", p_du_session_charging_information_local_JSON);
    if (item->child == NULL) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [p_du_session_charging_information]");
        goto end;
    }
    }

    if (charging_data_request->roaming_qbc_information) {
    cJSON *roaming_qbc_information_local_JSON = OpenAPI_roaming_qbc_information_convertToJSON(charging_data_request->roaming_qbc_information);
    if (roaming_qbc_information_local_JSON == NULL) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [roaming_qbc_information]");
        goto end;
    }
    cJSON_AddItemToObject(item, "roamingQBCInformation", roaming_qbc_information_local_JSON);
    if (item->child == NULL) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed [roaming_qbc_information]");
        goto end;
    }
    }

end:
    return item;
}

OpenAPI_charging_data_request_t *OpenAPI_charging_data_request_parseFromJSON(cJSON *charging_data_requestJSON)
{
    OpenAPI_charging_data_request_t *charging_data_request_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *subscriber_identifier = NULL;
    cJSON *nf_consumer_identification = NULL;
    OpenAPI_nf_identification_t *nf_consumer_identification_local_nonprim = NULL;
    cJSON *invocation_time_stamp = NULL;
    cJSON *invocation_sequence_number = NULL;
    cJSON *retransmission_indicator = NULL;
    cJSON *service_specification_info = NULL;
    cJSON *multiple_unit_usage = NULL;
    OpenAPI_list_t *multiple_unit_usageList = NULL;
    cJSON *triggers = NULL;
    OpenAPI_list_t *triggersList = NULL;
    cJSON *p_du_session_charging_information = NULL;
    OpenAPI_pdu_session_charging_information_t *p_du_session_charging_information_local_nonprim = NULL;
    cJSON *roaming_qbc_information = NULL;
    OpenAPI_roaming_qbc_information_t *roaming_qbc_information_local_nonprim = NULL;
    subscriber_identifier = cJSON_GetObjectItemCaseSensitive(charging_data_requestJSON, "subscriberIdentifier");
    if (subscriber_identifier) {
    if (!cJSON_IsString(subscriber_identifier) && !cJSON_IsNull(subscriber_identifier)) {
        ogs_error("OpenAPI_charging_data_request_parseFromJSON() failed [subscriber_identifier]");
        goto end;
    }
    }

    nf_consumer_identification = cJSON_GetObjectItemCaseSensitive(charging_data_requestJSON, "nfConsumerIdentification");
    if (!nf_consumer_identification) {
        ogs_error("OpenAPI_charging_data_request_parseFromJSON() failed [nf_consumer_identification]");
        goto end;
    }
    nf_consumer_identification_local_nonprim = OpenAPI_nf_identification_parseFromJSON(nf_consumer_identification);
    if (!nf_consumer_identification_local_nonprim) {
        ogs_error("OpenAPI_nf_identification_parseFromJSON failed [nf_consumer_identification]");
        goto end;
    }

    invocation_time_stamp = cJSON_GetObjectItemCaseSensitive(charging_data_requestJSON, "invocationTimeStamp");
    if (!invocation_time_stamp) {
        ogs_error("OpenAPI_charging_data_request_parseFromJSON() failed [invocation_time_stamp]");
        goto end;
    }
    if (!cJSON_IsString(invocation_time_stamp) && !cJSON_IsNull(invocation_time_stamp)) {
        ogs_error("OpenAPI_charging_data_request_parseFromJSON() failed [invocation_time_stamp]");
        goto end;
    }

    invocation_sequence_number = cJSON_GetObjectItemCaseSensitive(charging_data_requestJSON, "invocationSequenceNumber");
    if (!invocation_sequence_number) {
        ogs_error("OpenAPI_charging_data_request_parseFromJSON() failed [invocation_sequence_number]");
        goto end;
    }
    if (!cJSON_IsNumber(invocation_sequence_number)) {
        ogs_error("OpenAPI_charging_data_request_parseFromJSON() failed [invocation_sequence_number]");
        goto end;
    }

    retransmission_indicator = cJSON_GetObjectItemCaseSensitive(charging_data_requestJSON, "retransmissionIndicator");
    if (retransmission_indicator) {
    if (!cJSON_IsBool(retransmission_indicator)) {
        ogs_error("OpenAPI_charging_data_request_parseFromJSON() failed [retransmission_indicator]");
        goto end;
    }
    }

    service_specification_info = cJSON_GetObjectItemCaseSensitive(charging_data_requestJSON, "serviceSpecificationInfo");
    if (service_specification_info) {
    if (!cJSON_IsString(service_specification_info) && !cJSON_IsNull(service_specification_info)) {
        ogs_error("OpenAPI_charging_data_request_parseFromJSON() failed [service_specification_info]");
        goto end;
    }
    }

    multiple_unit_usage = cJSON_GetObjectItemCaseSensitive(charging_data_requestJSON, "multipleUnitUsage");
    if (multiple_unit_usage) {
        cJSON *multiple_unit_usage_local = NULL;
        if (!cJSON_IsArray(multiple_unit_usage)) {
            ogs_error("OpenAPI_charging_data_request_parseFromJSON() failed [multiple_unit_usage]");
            goto end;
        }

        multiple_unit_usageList = OpenAPI_list_create();

        cJSON_ArrayForEach(multiple_unit_usage_local, multiple_unit_usage) {
            if (!cJSON_IsObject(multiple_unit_usage_local)) {
                ogs_error("OpenAPI_charging_data_request_parseFromJSON() failed [multiple_unit_usage]");
                goto end;
            }
            OpenAPI_multiple_unit_usage_t *multiple_unit_usageItem = OpenAPI_multiple_unit_usage_parseFromJSON(multiple_unit_usage_local);
            if (!multiple_unit_usageItem) {
                ogs_error("No multiple_unit_usageItem");
                goto end;
            }
            OpenAPI_list_add(multiple_unit_usageList, multiple_unit_usageItem);
        }
    }

    triggers = cJSON_GetObjectItemCaseSensitive(charging_data_requestJSON, "triggers");
    if (triggers) {
        cJSON *triggers_local = NULL;
        if (!cJSON_IsArray(triggers)) {
            ogs_error("OpenAPI_charging_data_request_parseFromJSON() failed [triggers]");
            goto end;
        }

        triggersList = OpenAPI_list_create();

        cJSON_ArrayForEach(triggers_local, triggers) {
            if (!cJSON_IsObject(triggers_local)) {
                ogs_error("OpenAPI_charging_data_request_parseFromJSON() failed [triggers]");
                goto end;
            }
            OpenAPI_trigger_t *triggersItem = OpenAPI_trigger_parseFromJSON(triggers_local);
            if (!triggersItem) {
                ogs_error("No triggersItem");
                goto end;
            }
            OpenAPI_list_add(triggersList, triggersItem);
        }
    }

    p_du_session_charging_information = cJSON_GetObjectItemCaseSensitive(charging_data_requestJSON, "pDUSessionChargingInformation");
    if (p_du_session_charging_information) {
    p_du_session_charging_information_local_nonprim = OpenAPI_pdu_session_charging_information_parseFromJSON(p_du_session_charging_information);
    if (!p_du_session_charging_information_local_nonprim) {
        ogs_error("OpenAPI_pdu_session_charging_information_parseFromJSON failed [p_du_session_charging_information]");
        goto end;
    }
    }

    roaming_qbc_information = cJSON_GetObjectItemCaseSensitive(charging_data_requestJSON, "roamingQBCInformation");
    if (roaming_qbc_information) {
    roaming_qbc_information_local_nonprim = OpenAPI_roaming_qbc_information_parseFromJSON(roaming_qbc_information);
    if (!roaming_qbc_information_local_nonprim) {
        ogs_error("OpenAPI_roaming_qbc_information_parseFromJSON failed [roaming_qbc_information]");
        goto end;
    }
    }

    charging_data_request_local_var = OpenAPI_charging_data_request_create (
        subscriber_identifier && !cJSON_IsNull(subscriber_identifier) ? ogs_strdup(subscriber_identifier->valuestring) : NULL,
        nf_consumer_identification_local_nonprim,
        ogs_strdup(invocation_time_stamp->valuestring),
        
        invocation_sequence_number->valuedouble,
        retransmission_indicator ? true : false,
        retransmission_indicator ? retransmission_indicator->valueint : 0,
        service_specification_info && !cJSON_IsNull(service_specification_info) ? ogs_strdup(service_specification_info->valuestring) : NULL,
        multiple_unit_usage ? multiple_unit_usageList : NULL,
        triggers ? triggersList : NULL,
        p_du_session_charging_information ? p_du_session_charging_information_local_nonprim : NULL,
        roaming_qbc_information ? roaming_qbc_information_local_nonprim : NULL
    );

    return charging_data_request_local_var;
end:
    if (nf_consumer_identification_local_nonprim) {
        OpenAPI_nf_identification_free(nf_consumer_identification_local_nonprim);
        nf_consumer_identification_local_nonprim = NULL;
    }
    if (multiple_unit_usageList) {
        OpenAPI_list_for_each(multiple_unit_usageList, node) {
            OpenAPI_multiple_unit_usage_free(node->data);
        }
        OpenAPI_list_free(multiple_unit_usageList);
        multiple_unit_usageList = NULL;
    }
    if (triggersList) {
        OpenAPI_list_for_each(triggersList, node) {
            OpenAPI_trigger_free(node->data);
        }
        OpenAPI_list_free(triggersList);
        triggersList = NULL;
    }
    if (p_du_session_charging_information_local_nonprim) {
        OpenAPI_pdu_session_charging_information_free(p_du_session_charging_information_local_nonprim);
        p_du_session_charging_information_local_nonprim = NULL;
    }
    if (roaming_qbc_information_local_nonprim) {
        OpenAPI_roaming_qbc_information_free(roaming_qbc_information_local_nonprim);
        roaming_qbc_information_local_nonprim = NULL;
    }
    return NULL;
}

OpenAPI_charging_data_request_t *OpenAPI_charging_data_request_copy(OpenAPI_charging_data_request_t *dst, OpenAPI_charging_data_request_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_charging_data_request_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_charging_data_request_convertToJSON() failed");
        return NULL;
    }

    content = cJSON_Print(item);
    cJSON_Delete(item);

    if (!content) {
        ogs_error("cJSON_Print() failed");
        return NULL;
    }

    item = cJSON_Parse(content);
    ogs_free(content);
    if (!item) {
        ogs_error("cJSON_Parse() failed");
        return NULL;
    }

    OpenAPI_charging_data_request_free(dst);
    dst = OpenAPI_charging_data_request_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

