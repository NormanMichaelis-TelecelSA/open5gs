
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "service_experience_info.h"

OpenAPI_service_experience_info_t *OpenAPI_service_experience_info_create(
    OpenAPI_list_t *supis,
    OpenAPI_list_t *ue_locs,
)
{
    OpenAPI_service_experience_info_t *service_experience_info_local_var = ogs_malloc(sizeof(OpenAPI_service_experience_info_t));
    ogs_assert(service_experience_info_local_var);

    service_experience_info_local_var->svc_exprc = svc_exprc;
    service_experience_info_local_var->svc_exprc_variance = svc_exprc_variance;
    service_experience_info_local_var->supis = supis;
    service_experience_info_local_var->snssai = snssai;
    service_experience_info_local_var->app_id = app_id;
    service_experience_info_local_var->srv_expc_type = srv_expc_type;
    service_experience_info_local_var->ue_locs = ue_locs;
    service_experience_info_local_var->upf_info = upf_info;
    service_experience_info_local_var->dnai = dnai;
    service_experience_info_local_var->app_server_inst = app_server_inst;
    service_experience_info_local_var->confidence = confidence;
    service_experience_info_local_var->dnn = dnn;
    service_experience_info_local_var->network_area = network_area;
    service_experience_info_local_var->nsi_id = nsi_id;
    service_experience_info_local_var->ratio = ratio;
    service_experience_info_local_var->rat_freq = rat_freq;

    return service_experience_info_local_var;
}

void OpenAPI_service_experience_info_free(OpenAPI_service_experience_info_t *service_experience_info)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == service_experience_info) {
        return;
    }
    if (service_experience_info->supis) {
        OpenAPI_list_for_each(service_experience_info->supis, node) {
            OpenAPI_object_free(node->data);
        }
        OpenAPI_list_free(service_experience_info->supis);
        service_experience_info->supis = NULL;
    }
    if (service_experience_info->ue_locs) {
        OpenAPI_list_for_each(service_experience_info->ue_locs, node) {
            OpenAPI_location_info_free(node->data);
        }
        OpenAPI_list_free(service_experience_info->ue_locs);
        service_experience_info->ue_locs = NULL;
    }
    ogs_free(service_experience_info);
}

cJSON *OpenAPI_service_experience_info_convertToJSON(OpenAPI_service_experience_info_t *service_experience_info)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (service_experience_info == NULL) {
        ogs_error("OpenAPI_service_experience_info_convertToJSON() failed [ServiceExperienceInfo]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (!service_experience_info->svc_exprc) {
        ogs_error("OpenAPI_service_experience_info_convertToJSON() failed [svc_exprc]");
        return NULL;
    }

    if (service_experience_info->svc_exprc_variance) {
    }

    if (service_experience_info->supis) {
    cJSON *supisList = cJSON_AddArrayToObject(item, "supis");
    if (supisList == NULL) {
        ogs_error("OpenAPI_service_experience_info_convertToJSON() failed [supis]");
        goto end;
    }
    OpenAPI_list_for_each(service_experience_info->supis, node) {
        cJSON *itemLocal = OpenAPI_object_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_service_experience_info_convertToJSON() failed [supis]");
            goto end;
        }
        cJSON_AddItemToArray(supisList, itemLocal);
    }
    }

    if (service_experience_info->snssai) {
    }

    if (service_experience_info->app_id) {
    }

    if (service_experience_info->srv_expc_type) {
    }

    if (service_experience_info->ue_locs) {
    cJSON *ue_locsList = cJSON_AddArrayToObject(item, "ueLocs");
    if (ue_locsList == NULL) {
        ogs_error("OpenAPI_service_experience_info_convertToJSON() failed [ue_locs]");
        goto end;
    }
    OpenAPI_list_for_each(service_experience_info->ue_locs, node) {
        cJSON *itemLocal = OpenAPI_location_info_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_service_experience_info_convertToJSON() failed [ue_locs]");
            goto end;
        }
        cJSON_AddItemToArray(ue_locsList, itemLocal);
    }
    }

    if (service_experience_info->upf_info) {
    }

    if (service_experience_info->dnai) {
    }

    if (service_experience_info->app_server_inst) {
    }

    if (service_experience_info->confidence) {
    }

    if (service_experience_info->dnn) {
    }

    if (service_experience_info->network_area) {
    }

    if (service_experience_info->nsi_id) {
    }

    if (service_experience_info->ratio) {
    }

    if (service_experience_info->rat_freq) {
    }

end:
    return item;
}

OpenAPI_service_experience_info_t *OpenAPI_service_experience_info_parseFromJSON(cJSON *service_experience_infoJSON)
{
    OpenAPI_service_experience_info_t *service_experience_info_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *svc_exprc = NULL;
    cJSON *svc_exprc_variance = NULL;
    cJSON *supis = NULL;
    OpenAPI_list_t *supisList = NULL;
    cJSON *snssai = NULL;
    cJSON *app_id = NULL;
    cJSON *srv_expc_type = NULL;
    cJSON *ue_locs = NULL;
    OpenAPI_list_t *ue_locsList = NULL;
    cJSON *upf_info = NULL;
    cJSON *dnai = NULL;
    cJSON *app_server_inst = NULL;
    cJSON *confidence = NULL;
    cJSON *dnn = NULL;
    cJSON *network_area = NULL;
    cJSON *nsi_id = NULL;
    cJSON *ratio = NULL;
    cJSON *rat_freq = NULL;
    svc_exprc = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "svcExprc");
    if (!svc_exprc) {
        ogs_error("OpenAPI_service_experience_info_parseFromJSON() failed [svc_exprc]");
        goto end;
    }

    svc_exprc_variance = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "svcExprcVariance");
    if (svc_exprc_variance) {
    }

    supis = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "supis");
    if (supis) {
        cJSON *supis_local = NULL;
        if (!cJSON_IsArray(supis)) {
            ogs_error("OpenAPI_service_experience_info_parseFromJSON() failed [supis]");
            goto end;
        }

        supisList = OpenAPI_list_create();

        cJSON_ArrayForEach(supis_local, supis) {
            if (!cJSON_IsObject(supis_local)) {
                ogs_error("OpenAPI_service_experience_info_parseFromJSON() failed [supis]");
                goto end;
            }
            OpenAPI_object_t *supisItem = OpenAPI_object_parseFromJSON(supis_local);
            if (!supisItem) {
                ogs_error("No supisItem");
                goto end;
            }
            OpenAPI_list_add(supisList, supisItem);
        }
    }

    snssai = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "snssai");
    if (snssai) {
    }

    app_id = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "appId");
    if (app_id) {
    }

    srv_expc_type = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "srvExpcType");
    if (srv_expc_type) {
    }

    ue_locs = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "ueLocs");
    if (ue_locs) {
        cJSON *ue_locs_local = NULL;
        if (!cJSON_IsArray(ue_locs)) {
            ogs_error("OpenAPI_service_experience_info_parseFromJSON() failed [ue_locs]");
            goto end;
        }

        ue_locsList = OpenAPI_list_create();

        cJSON_ArrayForEach(ue_locs_local, ue_locs) {
            if (!cJSON_IsObject(ue_locs_local)) {
                ogs_error("OpenAPI_service_experience_info_parseFromJSON() failed [ue_locs]");
                goto end;
            }
            OpenAPI_location_info_t *ue_locsItem = OpenAPI_location_info_parseFromJSON(ue_locs_local);
            if (!ue_locsItem) {
                ogs_error("No ue_locsItem");
                goto end;
            }
            OpenAPI_list_add(ue_locsList, ue_locsItem);
        }
    }

    upf_info = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "upfInfo");
    if (upf_info) {
    }

    dnai = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "dnai");
    if (dnai) {
    }

    app_server_inst = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "appServerInst");
    if (app_server_inst) {
    }

    confidence = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "confidence");
    if (confidence) {
    }

    dnn = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "dnn");
    if (dnn) {
    }

    network_area = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "networkArea");
    if (network_area) {
    }

    nsi_id = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "nsiId");
    if (nsi_id) {
    }

    ratio = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "ratio");
    if (ratio) {
    }

    rat_freq = cJSON_GetObjectItemCaseSensitive(service_experience_infoJSON, "ratFreq");
    if (rat_freq) {
    }

    service_experience_info_local_var = OpenAPI_service_experience_info_create (
        supis ? supisList : NULL,
        ue_locs ? ue_locsList : NULL,
    );

    return service_experience_info_local_var;
end:
    if (supisList) {
        OpenAPI_list_for_each(supisList, node) {
            OpenAPI_object_free(node->data);
        }
        OpenAPI_list_free(supisList);
        supisList = NULL;
    }
    if (ue_locsList) {
        OpenAPI_list_for_each(ue_locsList, node) {
            OpenAPI_location_info_free(node->data);
        }
        OpenAPI_list_free(ue_locsList);
        ue_locsList = NULL;
    }
    return NULL;
}

OpenAPI_service_experience_info_t *OpenAPI_service_experience_info_copy(OpenAPI_service_experience_info_t *dst, OpenAPI_service_experience_info_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_service_experience_info_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_service_experience_info_convertToJSON() failed");
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

    OpenAPI_service_experience_info_free(dst);
    dst = OpenAPI_service_experience_info_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

