
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ip_addr.h"

OpenAPI_ip_addr_t *OpenAPI_ip_addr_create(
)
{
    OpenAPI_ip_addr_t *ip_addr_local_var = ogs_malloc(sizeof(OpenAPI_ip_addr_t));
    ogs_assert(ip_addr_local_var);

    ip_addr_local_var->ipv4_addr = ipv4_addr;
    ip_addr_local_var->ipv6_addr = ipv6_addr;
    ip_addr_local_var->ipv6_prefix = ipv6_prefix;

    return ip_addr_local_var;
}

void OpenAPI_ip_addr_free(OpenAPI_ip_addr_t *ip_addr)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == ip_addr) {
        return;
    }
    ogs_free(ip_addr);
}

cJSON *OpenAPI_ip_addr_convertToJSON(OpenAPI_ip_addr_t *ip_addr)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (ip_addr == NULL) {
        ogs_error("OpenAPI_ip_addr_convertToJSON() failed [IpAddr]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (ip_addr->ipv4_addr) {
    }

    if (ip_addr->ipv6_addr) {
    }

    if (ip_addr->ipv6_prefix) {
    }

end:
    return item;
}

OpenAPI_ip_addr_t *OpenAPI_ip_addr_parseFromJSON(cJSON *ip_addrJSON)
{
    OpenAPI_ip_addr_t *ip_addr_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *ipv4_addr = NULL;
    cJSON *ipv6_addr = NULL;
    cJSON *ipv6_prefix = NULL;
    ipv4_addr = cJSON_GetObjectItemCaseSensitive(ip_addrJSON, "ipv4Addr");
    if (ipv4_addr) {
    }

    ipv6_addr = cJSON_GetObjectItemCaseSensitive(ip_addrJSON, "ipv6Addr");
    if (ipv6_addr) {
    }

    ipv6_prefix = cJSON_GetObjectItemCaseSensitive(ip_addrJSON, "ipv6Prefix");
    if (ipv6_prefix) {
    }

    ip_addr_local_var = OpenAPI_ip_addr_create (
    );

    return ip_addr_local_var;
end:
    return NULL;
}

OpenAPI_ip_addr_t *OpenAPI_ip_addr_copy(OpenAPI_ip_addr_t *dst, OpenAPI_ip_addr_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_ip_addr_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_ip_addr_convertToJSON() failed");
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

    OpenAPI_ip_addr_free(dst);
    dst = OpenAPI_ip_addr_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

