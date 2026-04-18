
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "nsi_load_level_info.h"

OpenAPI_nsi_load_level_info_t *OpenAPI_nsi_load_level_info_create(
    bool is_exceed_load_level_thr_ind,
    int exceed_load_level_thr_ind,
    OpenAPI_list_t *res_usg_thr_cross_time_period,
)
{
    OpenAPI_nsi_load_level_info_t *nsi_load_level_info_local_var = ogs_malloc(sizeof(OpenAPI_nsi_load_level_info_t));
    ogs_assert(nsi_load_level_info_local_var);

    nsi_load_level_info_local_var->load_level_information = load_level_information;
    nsi_load_level_info_local_var->snssai = snssai;
    nsi_load_level_info_local_var->nsi_id = nsi_id;
    nsi_load_level_info_local_var->res_usage = res_usage;
    nsi_load_level_info_local_var->num_of_exceed_load_level_thr = num_of_exceed_load_level_thr;
    nsi_load_level_info_local_var->is_exceed_load_level_thr_ind = is_exceed_load_level_thr_ind;
    nsi_load_level_info_local_var->exceed_load_level_thr_ind = exceed_load_level_thr_ind;
    nsi_load_level_info_local_var->network_area = network_area;
    nsi_load_level_info_local_var->time_period = time_period;
    nsi_load_level_info_local_var->res_usg_thr_cross_time_period = res_usg_thr_cross_time_period;
    nsi_load_level_info_local_var->num_of_ues = num_of_ues;
    nsi_load_level_info_local_var->num_of_pdu_sess = num_of_pdu_sess;
    nsi_load_level_info_local_var->confidence = confidence;

    return nsi_load_level_info_local_var;
}

void OpenAPI_nsi_load_level_info_free(OpenAPI_nsi_load_level_info_t *nsi_load_level_info)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == nsi_load_level_info) {
        return;
    }
    if (nsi_load_level_info->res_usg_thr_cross_time_period) {
        OpenAPI_list_for_each(nsi_load_level_info->res_usg_thr_cross_time_period, node) {
            OpenAPI_object_free(node->data);
        }
        OpenAPI_list_free(nsi_load_level_info->res_usg_thr_cross_time_period);
        nsi_load_level_info->res_usg_thr_cross_time_period = NULL;
    }
    ogs_free(nsi_load_level_info);
}

cJSON *OpenAPI_nsi_load_level_info_convertToJSON(OpenAPI_nsi_load_level_info_t *nsi_load_level_info)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (nsi_load_level_info == NULL) {
        ogs_error("OpenAPI_nsi_load_level_info_convertToJSON() failed [NsiLoadLevelInfo]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (!nsi_load_level_info->load_level_information) {
        ogs_error("OpenAPI_nsi_load_level_info_convertToJSON() failed [load_level_information]");
        return NULL;
    }

    if (!nsi_load_level_info->snssai) {
        ogs_error("OpenAPI_nsi_load_level_info_convertToJSON() failed [snssai]");
        return NULL;
    }

    if (nsi_load_level_info->nsi_id) {
    }

    if (nsi_load_level_info->res_usage) {
    }

    if (nsi_load_level_info->num_of_exceed_load_level_thr) {
    }

    if (nsi_load_level_info->is_exceed_load_level_thr_ind) {
    if (cJSON_AddBoolToObject(item, "exceedLoadLevelThrInd", nsi_load_level_info->exceed_load_level_thr_ind) == NULL) {
        ogs_error("OpenAPI_nsi_load_level_info_convertToJSON() failed [exceed_load_level_thr_ind]");
        goto end;
    }
    }

    if (nsi_load_level_info->network_area) {
    }

    if (nsi_load_level_info->time_period) {
    }

    if (nsi_load_level_info->res_usg_thr_cross_time_period) {
    cJSON *res_usg_thr_cross_time_periodList = cJSON_AddArrayToObject(item, "resUsgThrCrossTimePeriod");
    if (res_usg_thr_cross_time_periodList == NULL) {
        ogs_error("OpenAPI_nsi_load_level_info_convertToJSON() failed [res_usg_thr_cross_time_period]");
        goto end;
    }
    OpenAPI_list_for_each(nsi_load_level_info->res_usg_thr_cross_time_period, node) {
        cJSON *itemLocal = OpenAPI_object_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_nsi_load_level_info_convertToJSON() failed [res_usg_thr_cross_time_period]");
            goto end;
        }
        cJSON_AddItemToArray(res_usg_thr_cross_time_periodList, itemLocal);
    }
    }

    if (nsi_load_level_info->num_of_ues) {
    }

    if (nsi_load_level_info->num_of_pdu_sess) {
    }

    if (nsi_load_level_info->confidence) {
    }

end:
    return item;
}

OpenAPI_nsi_load_level_info_t *OpenAPI_nsi_load_level_info_parseFromJSON(cJSON *nsi_load_level_infoJSON)
{
    OpenAPI_nsi_load_level_info_t *nsi_load_level_info_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *load_level_information = NULL;
    cJSON *snssai = NULL;
    cJSON *nsi_id = NULL;
    cJSON *res_usage = NULL;
    cJSON *num_of_exceed_load_level_thr = NULL;
    cJSON *exceed_load_level_thr_ind = NULL;
    cJSON *network_area = NULL;
    cJSON *time_period = NULL;
    cJSON *res_usg_thr_cross_time_period = NULL;
    OpenAPI_list_t *res_usg_thr_cross_time_periodList = NULL;
    cJSON *num_of_ues = NULL;
    cJSON *num_of_pdu_sess = NULL;
    cJSON *confidence = NULL;
    load_level_information = cJSON_GetObjectItemCaseSensitive(nsi_load_level_infoJSON, "loadLevelInformation");
    if (!load_level_information) {
        ogs_error("OpenAPI_nsi_load_level_info_parseFromJSON() failed [load_level_information]");
        goto end;
    }

    snssai = cJSON_GetObjectItemCaseSensitive(nsi_load_level_infoJSON, "snssai");
    if (!snssai) {
        ogs_error("OpenAPI_nsi_load_level_info_parseFromJSON() failed [snssai]");
        goto end;
    }

    nsi_id = cJSON_GetObjectItemCaseSensitive(nsi_load_level_infoJSON, "nsiId");
    if (nsi_id) {
    }

    res_usage = cJSON_GetObjectItemCaseSensitive(nsi_load_level_infoJSON, "resUsage");
    if (res_usage) {
    }

    num_of_exceed_load_level_thr = cJSON_GetObjectItemCaseSensitive(nsi_load_level_infoJSON, "numOfExceedLoadLevelThr");
    if (num_of_exceed_load_level_thr) {
    }

    exceed_load_level_thr_ind = cJSON_GetObjectItemCaseSensitive(nsi_load_level_infoJSON, "exceedLoadLevelThrInd");
    if (exceed_load_level_thr_ind) {
    if (!cJSON_IsBool(exceed_load_level_thr_ind)) {
        ogs_error("OpenAPI_nsi_load_level_info_parseFromJSON() failed [exceed_load_level_thr_ind]");
        goto end;
    }
    }

    network_area = cJSON_GetObjectItemCaseSensitive(nsi_load_level_infoJSON, "networkArea");
    if (network_area) {
    }

    time_period = cJSON_GetObjectItemCaseSensitive(nsi_load_level_infoJSON, "timePeriod");
    if (time_period) {
    }

    res_usg_thr_cross_time_period = cJSON_GetObjectItemCaseSensitive(nsi_load_level_infoJSON, "resUsgThrCrossTimePeriod");
    if (res_usg_thr_cross_time_period) {
        cJSON *res_usg_thr_cross_time_period_local = NULL;
        if (!cJSON_IsArray(res_usg_thr_cross_time_period)) {
            ogs_error("OpenAPI_nsi_load_level_info_parseFromJSON() failed [res_usg_thr_cross_time_period]");
            goto end;
        }

        res_usg_thr_cross_time_periodList = OpenAPI_list_create();

        cJSON_ArrayForEach(res_usg_thr_cross_time_period_local, res_usg_thr_cross_time_period) {
            if (!cJSON_IsObject(res_usg_thr_cross_time_period_local)) {
                ogs_error("OpenAPI_nsi_load_level_info_parseFromJSON() failed [res_usg_thr_cross_time_period]");
                goto end;
            }
            OpenAPI_object_t *res_usg_thr_cross_time_periodItem = OpenAPI_object_parseFromJSON(res_usg_thr_cross_time_period_local);
            if (!res_usg_thr_cross_time_periodItem) {
                ogs_error("No res_usg_thr_cross_time_periodItem");
                goto end;
            }
            OpenAPI_list_add(res_usg_thr_cross_time_periodList, res_usg_thr_cross_time_periodItem);
        }
    }

    num_of_ues = cJSON_GetObjectItemCaseSensitive(nsi_load_level_infoJSON, "numOfUes");
    if (num_of_ues) {
    }

    num_of_pdu_sess = cJSON_GetObjectItemCaseSensitive(nsi_load_level_infoJSON, "numOfPduSess");
    if (num_of_pdu_sess) {
    }

    confidence = cJSON_GetObjectItemCaseSensitive(nsi_load_level_infoJSON, "confidence");
    if (confidence) {
    }

    nsi_load_level_info_local_var = OpenAPI_nsi_load_level_info_create (
        exceed_load_level_thr_ind ? true : false,
        exceed_load_level_thr_ind ? exceed_load_level_thr_ind->valueint : 0,
        res_usg_thr_cross_time_period ? res_usg_thr_cross_time_periodList : NULL,
    );

    return nsi_load_level_info_local_var;
end:
    if (res_usg_thr_cross_time_periodList) {
        OpenAPI_list_for_each(res_usg_thr_cross_time_periodList, node) {
            OpenAPI_object_free(node->data);
        }
        OpenAPI_list_free(res_usg_thr_cross_time_periodList);
        res_usg_thr_cross_time_periodList = NULL;
    }
    return NULL;
}

OpenAPI_nsi_load_level_info_t *OpenAPI_nsi_load_level_info_copy(OpenAPI_nsi_load_level_info_t *dst, OpenAPI_nsi_load_level_info_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_nsi_load_level_info_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_nsi_load_level_info_convertToJSON() failed");
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

    OpenAPI_nsi_load_level_info_free(dst);
    dst = OpenAPI_nsi_load_level_info_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

