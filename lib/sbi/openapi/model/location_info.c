
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "location_info.h"

OpenAPI_location_info_t *OpenAPI_location_info_create(
)
{
    OpenAPI_location_info_t *location_info_local_var = ogs_malloc(sizeof(OpenAPI_location_info_t));
    ogs_assert(location_info_local_var);

    location_info_local_var->loc = loc;
    location_info_local_var->ratio = ratio;
    location_info_local_var->confidence = confidence;

    return location_info_local_var;
}

void OpenAPI_location_info_free(OpenAPI_location_info_t *location_info)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == location_info) {
        return;
    }
    ogs_free(location_info);
}

cJSON *OpenAPI_location_info_convertToJSON(OpenAPI_location_info_t *location_info)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (location_info == NULL) {
        ogs_error("OpenAPI_location_info_convertToJSON() failed [LocationInfo]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (!location_info->loc) {
        ogs_error("OpenAPI_location_info_convertToJSON() failed [loc]");
        return NULL;
    }

    if (location_info->ratio) {
    }

    if (location_info->confidence) {
    }

end:
    return item;
}

OpenAPI_location_info_t *OpenAPI_location_info_parseFromJSON(cJSON *location_infoJSON)
{
    OpenAPI_location_info_t *location_info_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *loc = NULL;
    cJSON *ratio = NULL;
    cJSON *confidence = NULL;
    loc = cJSON_GetObjectItemCaseSensitive(location_infoJSON, "loc");
    if (!loc) {
        ogs_error("OpenAPI_location_info_parseFromJSON() failed [loc]");
        goto end;
    }

    ratio = cJSON_GetObjectItemCaseSensitive(location_infoJSON, "ratio");
    if (ratio) {
    }

    confidence = cJSON_GetObjectItemCaseSensitive(location_infoJSON, "confidence");
    if (confidence) {
    }

    location_info_local_var = OpenAPI_location_info_create (
    );

    return location_info_local_var;
end:
    return NULL;
}

OpenAPI_location_info_t *OpenAPI_location_info_copy(OpenAPI_location_info_t *dst, OpenAPI_location_info_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_location_info_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_location_info_convertToJSON() failed");
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

    OpenAPI_location_info_free(dst);
    dst = OpenAPI_location_info_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

