
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "eas_requirements.h"

OpenAPI_eas_requirements_t *OpenAPI_eas_requirements_create(
    bool is_service_continuity,
    int service_continuity,
)
{
    OpenAPI_eas_requirements_t *eas_requirements_local_var = ogs_malloc(sizeof(OpenAPI_eas_requirements_t));
    ogs_assert(eas_requirements_local_var);

    eas_requirements_local_var->required_ea_sserving_location = required_ea_sserving_location;
    eas_requirements_local_var->software_image_info = software_image_info;
    eas_requirements_local_var->affinity_anti_affinity = affinity_anti_affinity;
    eas_requirements_local_var->is_service_continuity = is_service_continuity;
    eas_requirements_local_var->service_continuity = service_continuity;
    eas_requirements_local_var->virtual_resource = virtual_resource;

    return eas_requirements_local_var;
}

void OpenAPI_eas_requirements_free(OpenAPI_eas_requirements_t *eas_requirements)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == eas_requirements) {
        return;
    }
    ogs_free(eas_requirements);
}

cJSON *OpenAPI_eas_requirements_convertToJSON(OpenAPI_eas_requirements_t *eas_requirements)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (eas_requirements == NULL) {
        ogs_error("OpenAPI_eas_requirements_convertToJSON() failed [EASRequirements]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (eas_requirements->required_ea_sserving_location) {
    }

    if (eas_requirements->software_image_info) {
    }

    if (eas_requirements->affinity_anti_affinity) {
    }

    if (eas_requirements->is_service_continuity) {
    if (cJSON_AddBoolToObject(item, "serviceContinuity", eas_requirements->service_continuity) == NULL) {
        ogs_error("OpenAPI_eas_requirements_convertToJSON() failed [service_continuity]");
        goto end;
    }
    }

    if (eas_requirements->virtual_resource) {
    }

end:
    return item;
}

OpenAPI_eas_requirements_t *OpenAPI_eas_requirements_parseFromJSON(cJSON *eas_requirementsJSON)
{
    OpenAPI_eas_requirements_t *eas_requirements_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *required_ea_sserving_location = NULL;
    cJSON *software_image_info = NULL;
    cJSON *affinity_anti_affinity = NULL;
    cJSON *service_continuity = NULL;
    cJSON *virtual_resource = NULL;
    required_ea_sserving_location = cJSON_GetObjectItemCaseSensitive(eas_requirementsJSON, "requiredEASservingLocation");
    if (required_ea_sserving_location) {
    }

    software_image_info = cJSON_GetObjectItemCaseSensitive(eas_requirementsJSON, "softwareImageInfo");
    if (software_image_info) {
    }

    affinity_anti_affinity = cJSON_GetObjectItemCaseSensitive(eas_requirementsJSON, "affinityAntiAffinity");
    if (affinity_anti_affinity) {
    }

    service_continuity = cJSON_GetObjectItemCaseSensitive(eas_requirementsJSON, "serviceContinuity");
    if (service_continuity) {
    if (!cJSON_IsBool(service_continuity)) {
        ogs_error("OpenAPI_eas_requirements_parseFromJSON() failed [service_continuity]");
        goto end;
    }
    }

    virtual_resource = cJSON_GetObjectItemCaseSensitive(eas_requirementsJSON, "virtualResource");
    if (virtual_resource) {
    }

    eas_requirements_local_var = OpenAPI_eas_requirements_create (
        service_continuity ? true : false,
        service_continuity ? service_continuity->valueint : 0,
    );

    return eas_requirements_local_var;
end:
    return NULL;
}

OpenAPI_eas_requirements_t *OpenAPI_eas_requirements_copy(OpenAPI_eas_requirements_t *dst, OpenAPI_eas_requirements_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_eas_requirements_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_eas_requirements_convertToJSON() failed");
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

    OpenAPI_eas_requirements_free(dst);
    dst = OpenAPI_eas_requirements_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

