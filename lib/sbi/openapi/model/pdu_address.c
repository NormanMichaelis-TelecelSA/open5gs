
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pdu_address.h"

OpenAPI_pdu_address_t *OpenAPI_pdu_address_create(
    char *pdu_ipv4_address,
    char *pdu_ipv6_addresswith_prefix,
    bool is_pdu_addressprefixlength,
    int pdu_addressprefixlength,
    bool is_i_pv4dynamic_address_flag,
    int i_pv4dynamic_address_flag,
    bool is_i_pv6dynamic_prefix_flag,
    int i_pv6dynamic_prefix_flag
)
{
    OpenAPI_pdu_address_t *pdu_address_local_var = ogs_malloc(sizeof(OpenAPI_pdu_address_t));
    ogs_assert(pdu_address_local_var);

    pdu_address_local_var->pdu_ipv4_address = pdu_ipv4_address;
    pdu_address_local_var->pdu_ipv6_addresswith_prefix = pdu_ipv6_addresswith_prefix;
    pdu_address_local_var->is_pdu_addressprefixlength = is_pdu_addressprefixlength;
    pdu_address_local_var->pdu_addressprefixlength = pdu_addressprefixlength;
    pdu_address_local_var->is_i_pv4dynamic_address_flag = is_i_pv4dynamic_address_flag;
    pdu_address_local_var->i_pv4dynamic_address_flag = i_pv4dynamic_address_flag;
    pdu_address_local_var->is_i_pv6dynamic_prefix_flag = is_i_pv6dynamic_prefix_flag;
    pdu_address_local_var->i_pv6dynamic_prefix_flag = i_pv6dynamic_prefix_flag;

    return pdu_address_local_var;
}

void OpenAPI_pdu_address_free(OpenAPI_pdu_address_t *pdu_address)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == pdu_address) {
        return;
    }
    if (pdu_address->pdu_ipv4_address) {
        ogs_free(pdu_address->pdu_ipv4_address);
        pdu_address->pdu_ipv4_address = NULL;
    }
    if (pdu_address->pdu_ipv6_addresswith_prefix) {
        ogs_free(pdu_address->pdu_ipv6_addresswith_prefix);
        pdu_address->pdu_ipv6_addresswith_prefix = NULL;
    }
    ogs_free(pdu_address);
}

cJSON *OpenAPI_pdu_address_convertToJSON(OpenAPI_pdu_address_t *pdu_address)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (pdu_address == NULL) {
        ogs_error("OpenAPI_pdu_address_convertToJSON() failed [PDUAddress]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (pdu_address->pdu_ipv4_address) {
    if (cJSON_AddStringToObject(item, "pduIPv4Address", pdu_address->pdu_ipv4_address) == NULL) {
        ogs_error("OpenAPI_pdu_address_convertToJSON() failed [pdu_ipv4_address]");
        goto end;
    }
    }

    if (pdu_address->pdu_ipv6_addresswith_prefix) {
    if (cJSON_AddStringToObject(item, "pduIPv6AddresswithPrefix", pdu_address->pdu_ipv6_addresswith_prefix) == NULL) {
        ogs_error("OpenAPI_pdu_address_convertToJSON() failed [pdu_ipv6_addresswith_prefix]");
        goto end;
    }
    }

    if (pdu_address->is_pdu_addressprefixlength) {
    if (cJSON_AddNumberToObject(item, "pduAddressprefixlength", pdu_address->pdu_addressprefixlength) == NULL) {
        ogs_error("OpenAPI_pdu_address_convertToJSON() failed [pdu_addressprefixlength]");
        goto end;
    }
    }

    if (pdu_address->is_i_pv4dynamic_address_flag) {
    if (cJSON_AddBoolToObject(item, "iPv4dynamicAddressFlag", pdu_address->i_pv4dynamic_address_flag) == NULL) {
        ogs_error("OpenAPI_pdu_address_convertToJSON() failed [i_pv4dynamic_address_flag]");
        goto end;
    }
    }

    if (pdu_address->is_i_pv6dynamic_prefix_flag) {
    if (cJSON_AddBoolToObject(item, "iPv6dynamicPrefixFlag", pdu_address->i_pv6dynamic_prefix_flag) == NULL) {
        ogs_error("OpenAPI_pdu_address_convertToJSON() failed [i_pv6dynamic_prefix_flag]");
        goto end;
    }
    }

end:
    return item;
}

OpenAPI_pdu_address_t *OpenAPI_pdu_address_parseFromJSON(cJSON *pdu_addressJSON)
{
    OpenAPI_pdu_address_t *pdu_address_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *pdu_ipv4_address = NULL;
    cJSON *pdu_ipv6_addresswith_prefix = NULL;
    cJSON *pdu_addressprefixlength = NULL;
    cJSON *i_pv4dynamic_address_flag = NULL;
    cJSON *i_pv6dynamic_prefix_flag = NULL;
    pdu_ipv4_address = cJSON_GetObjectItemCaseSensitive(pdu_addressJSON, "pduIPv4Address");
    if (pdu_ipv4_address) {
    if (!cJSON_IsString(pdu_ipv4_address) && !cJSON_IsNull(pdu_ipv4_address)) {
        ogs_error("OpenAPI_pdu_address_parseFromJSON() failed [pdu_ipv4_address]");
        goto end;
    }
    }

    pdu_ipv6_addresswith_prefix = cJSON_GetObjectItemCaseSensitive(pdu_addressJSON, "pduIPv6AddresswithPrefix");
    if (pdu_ipv6_addresswith_prefix) {
    if (!cJSON_IsString(pdu_ipv6_addresswith_prefix) && !cJSON_IsNull(pdu_ipv6_addresswith_prefix)) {
        ogs_error("OpenAPI_pdu_address_parseFromJSON() failed [pdu_ipv6_addresswith_prefix]");
        goto end;
    }
    }

    pdu_addressprefixlength = cJSON_GetObjectItemCaseSensitive(pdu_addressJSON, "pduAddressprefixlength");
    if (pdu_addressprefixlength) {
    if (!cJSON_IsNumber(pdu_addressprefixlength)) {
        ogs_error("OpenAPI_pdu_address_parseFromJSON() failed [pdu_addressprefixlength]");
        goto end;
    }
    }

    i_pv4dynamic_address_flag = cJSON_GetObjectItemCaseSensitive(pdu_addressJSON, "iPv4dynamicAddressFlag");
    if (i_pv4dynamic_address_flag) {
    if (!cJSON_IsBool(i_pv4dynamic_address_flag)) {
        ogs_error("OpenAPI_pdu_address_parseFromJSON() failed [i_pv4dynamic_address_flag]");
        goto end;
    }
    }

    i_pv6dynamic_prefix_flag = cJSON_GetObjectItemCaseSensitive(pdu_addressJSON, "iPv6dynamicPrefixFlag");
    if (i_pv6dynamic_prefix_flag) {
    if (!cJSON_IsBool(i_pv6dynamic_prefix_flag)) {
        ogs_error("OpenAPI_pdu_address_parseFromJSON() failed [i_pv6dynamic_prefix_flag]");
        goto end;
    }
    }

    pdu_address_local_var = OpenAPI_pdu_address_create (
        pdu_ipv4_address && !cJSON_IsNull(pdu_ipv4_address) ? ogs_strdup(pdu_ipv4_address->valuestring) : NULL,
        pdu_ipv6_addresswith_prefix && !cJSON_IsNull(pdu_ipv6_addresswith_prefix) ? ogs_strdup(pdu_ipv6_addresswith_prefix->valuestring) : NULL,
        pdu_addressprefixlength ? true : false,
        pdu_addressprefixlength ? pdu_addressprefixlength->valuedouble : 0,
        i_pv4dynamic_address_flag ? true : false,
        i_pv4dynamic_address_flag ? i_pv4dynamic_address_flag->valueint : 0,
        i_pv6dynamic_prefix_flag ? true : false,
        i_pv6dynamic_prefix_flag ? i_pv6dynamic_prefix_flag->valueint : 0
    );

    return pdu_address_local_var;
end:
    return NULL;
}

OpenAPI_pdu_address_t *OpenAPI_pdu_address_copy(OpenAPI_pdu_address_t *dst, OpenAPI_pdu_address_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_pdu_address_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_pdu_address_convertToJSON() failed");
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

    OpenAPI_pdu_address_free(dst);
    dst = OpenAPI_pdu_address_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

