
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "service_area_restriction.h"

OpenAPI_service_area_restriction_t *OpenAPI_service_area_restriction_create(
    OpenAPI_list_t *areas,
)
{
    OpenAPI_service_area_restriction_t *service_area_restriction_local_var = ogs_malloc(sizeof(OpenAPI_service_area_restriction_t));
    ogs_assert(service_area_restriction_local_var);

    service_area_restriction_local_var->restriction_type = restriction_type;
    service_area_restriction_local_var->areas = areas;
    service_area_restriction_local_var->max_num_of_tas = max_num_of_tas;
    service_area_restriction_local_var->max_num_of_tas_for_not_allowed_areas = max_num_of_tas_for_not_allowed_areas;

    return service_area_restriction_local_var;
}

void OpenAPI_service_area_restriction_free(OpenAPI_service_area_restriction_t *service_area_restriction)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == service_area_restriction) {
        return;
    }
    if (service_area_restriction->areas) {
        OpenAPI_list_for_each(service_area_restriction->areas, node) {
            OpenAPI_area_free(node->data);
        }
        OpenAPI_list_free(service_area_restriction->areas);
        service_area_restriction->areas = NULL;
    }
    ogs_free(service_area_restriction);
}

cJSON *OpenAPI_service_area_restriction_convertToJSON(OpenAPI_service_area_restriction_t *service_area_restriction)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (service_area_restriction == NULL) {
        ogs_error("OpenAPI_service_area_restriction_convertToJSON() failed [ServiceAreaRestriction]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (service_area_restriction->restriction_type) {
    }

    if (service_area_restriction->areas) {
    cJSON *areasList = cJSON_AddArrayToObject(item, "areas");
    if (areasList == NULL) {
        ogs_error("OpenAPI_service_area_restriction_convertToJSON() failed [areas]");
        goto end;
    }
    OpenAPI_list_for_each(service_area_restriction->areas, node) {
        cJSON *itemLocal = OpenAPI_area_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_service_area_restriction_convertToJSON() failed [areas]");
            goto end;
        }
        cJSON_AddItemToArray(areasList, itemLocal);
    }
    }

    if (service_area_restriction->max_num_of_tas) {
    }

    if (service_area_restriction->max_num_of_tas_for_not_allowed_areas) {
    }

end:
    return item;
}

OpenAPI_service_area_restriction_t *OpenAPI_service_area_restriction_parseFromJSON(cJSON *service_area_restrictionJSON)
{
    OpenAPI_service_area_restriction_t *service_area_restriction_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *restriction_type = NULL;
    cJSON *areas = NULL;
    OpenAPI_list_t *areasList = NULL;
    cJSON *max_num_of_tas = NULL;
    cJSON *max_num_of_tas_for_not_allowed_areas = NULL;
    restriction_type = cJSON_GetObjectItemCaseSensitive(service_area_restrictionJSON, "restrictionType");
    if (restriction_type) {
    }

    areas = cJSON_GetObjectItemCaseSensitive(service_area_restrictionJSON, "areas");
    if (areas) {
        cJSON *areas_local = NULL;
        if (!cJSON_IsArray(areas)) {
            ogs_error("OpenAPI_service_area_restriction_parseFromJSON() failed [areas]");
            goto end;
        }

        areasList = OpenAPI_list_create();

        cJSON_ArrayForEach(areas_local, areas) {
            if (!cJSON_IsObject(areas_local)) {
                ogs_error("OpenAPI_service_area_restriction_parseFromJSON() failed [areas]");
                goto end;
            }
            OpenAPI_area_t *areasItem = OpenAPI_area_parseFromJSON(areas_local);
            if (!areasItem) {
                ogs_error("No areasItem");
                goto end;
            }
            OpenAPI_list_add(areasList, areasItem);
        }
    }

    max_num_of_tas = cJSON_GetObjectItemCaseSensitive(service_area_restrictionJSON, "maxNumOfTAs");
    if (max_num_of_tas) {
    }

    max_num_of_tas_for_not_allowed_areas = cJSON_GetObjectItemCaseSensitive(service_area_restrictionJSON, "maxNumOfTAsForNotAllowedAreas");
    if (max_num_of_tas_for_not_allowed_areas) {
    }

    service_area_restriction_local_var = OpenAPI_service_area_restriction_create (
        areas ? areasList : NULL,
    );

    return service_area_restriction_local_var;
end:
    if (areasList) {
        OpenAPI_list_for_each(areasList, node) {
            OpenAPI_area_free(node->data);
        }
        OpenAPI_list_free(areasList);
        areasList = NULL;
    }
    return NULL;
}

OpenAPI_service_area_restriction_t *OpenAPI_service_area_restriction_copy(OpenAPI_service_area_restriction_t *dst, OpenAPI_service_area_restriction_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_service_area_restriction_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_service_area_restriction_convertToJSON() failed");
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

    OpenAPI_service_area_restriction_free(dst);
    dst = OpenAPI_service_area_restriction_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

