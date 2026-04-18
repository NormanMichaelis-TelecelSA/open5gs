
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "resource_usage.h"

OpenAPI_resource_usage_t *OpenAPI_resource_usage_create(
)
{
    OpenAPI_resource_usage_t *resource_usage_local_var = ogs_malloc(sizeof(OpenAPI_resource_usage_t));
    ogs_assert(resource_usage_local_var);

    resource_usage_local_var->cpu_usage = cpu_usage;
    resource_usage_local_var->memory_usage = memory_usage;
    resource_usage_local_var->storage_usage = storage_usage;

    return resource_usage_local_var;
}

void OpenAPI_resource_usage_free(OpenAPI_resource_usage_t *resource_usage)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == resource_usage) {
        return;
    }
    ogs_free(resource_usage);
}

cJSON *OpenAPI_resource_usage_convertToJSON(OpenAPI_resource_usage_t *resource_usage)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (resource_usage == NULL) {
        ogs_error("OpenAPI_resource_usage_convertToJSON() failed [ResourceUsage]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (resource_usage->cpu_usage) {
    }

    if (resource_usage->memory_usage) {
    }

    if (resource_usage->storage_usage) {
    }

end:
    return item;
}

OpenAPI_resource_usage_t *OpenAPI_resource_usage_parseFromJSON(cJSON *resource_usageJSON)
{
    OpenAPI_resource_usage_t *resource_usage_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *cpu_usage = NULL;
    cJSON *memory_usage = NULL;
    cJSON *storage_usage = NULL;
    cpu_usage = cJSON_GetObjectItemCaseSensitive(resource_usageJSON, "cpuUsage");
    if (cpu_usage) {
    }

    memory_usage = cJSON_GetObjectItemCaseSensitive(resource_usageJSON, "memoryUsage");
    if (memory_usage) {
    }

    storage_usage = cJSON_GetObjectItemCaseSensitive(resource_usageJSON, "storageUsage");
    if (storage_usage) {
    }

    resource_usage_local_var = OpenAPI_resource_usage_create (
    );

    return resource_usage_local_var;
end:
    return NULL;
}

OpenAPI_resource_usage_t *OpenAPI_resource_usage_copy(OpenAPI_resource_usage_t *dst, OpenAPI_resource_usage_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_resource_usage_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_resource_usage_convertToJSON() failed");
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

    OpenAPI_resource_usage_free(dst);
    dst = OpenAPI_resource_usage_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

