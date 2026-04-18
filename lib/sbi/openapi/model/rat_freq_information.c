
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rat_freq_information.h"

OpenAPI_rat_freq_information_t *OpenAPI_rat_freq_information_create(
    bool is_all_freq,
    int all_freq,
    bool is_all_rat,
    int all_rat,
)
{
    OpenAPI_rat_freq_information_t *rat_freq_information_local_var = ogs_malloc(sizeof(OpenAPI_rat_freq_information_t));
    ogs_assert(rat_freq_information_local_var);

    rat_freq_information_local_var->is_all_freq = is_all_freq;
    rat_freq_information_local_var->all_freq = all_freq;
    rat_freq_information_local_var->is_all_rat = is_all_rat;
    rat_freq_information_local_var->all_rat = all_rat;
    rat_freq_information_local_var->freq = freq;
    rat_freq_information_local_var->rat_type = rat_type;
    rat_freq_information_local_var->svc_exp_threshold = svc_exp_threshold;
    rat_freq_information_local_var->matching_dir = matching_dir;

    return rat_freq_information_local_var;
}

void OpenAPI_rat_freq_information_free(OpenAPI_rat_freq_information_t *rat_freq_information)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == rat_freq_information) {
        return;
    }
    ogs_free(rat_freq_information);
}

cJSON *OpenAPI_rat_freq_information_convertToJSON(OpenAPI_rat_freq_information_t *rat_freq_information)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (rat_freq_information == NULL) {
        ogs_error("OpenAPI_rat_freq_information_convertToJSON() failed [RatFreqInformation]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (rat_freq_information->is_all_freq) {
    if (cJSON_AddBoolToObject(item, "allFreq", rat_freq_information->all_freq) == NULL) {
        ogs_error("OpenAPI_rat_freq_information_convertToJSON() failed [all_freq]");
        goto end;
    }
    }

    if (rat_freq_information->is_all_rat) {
    if (cJSON_AddBoolToObject(item, "allRat", rat_freq_information->all_rat) == NULL) {
        ogs_error("OpenAPI_rat_freq_information_convertToJSON() failed [all_rat]");
        goto end;
    }
    }

    if (rat_freq_information->freq) {
    }

    if (rat_freq_information->rat_type) {
    }

    if (rat_freq_information->svc_exp_threshold) {
    }

    if (rat_freq_information->matching_dir) {
    }

end:
    return item;
}

OpenAPI_rat_freq_information_t *OpenAPI_rat_freq_information_parseFromJSON(cJSON *rat_freq_informationJSON)
{
    OpenAPI_rat_freq_information_t *rat_freq_information_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *all_freq = NULL;
    cJSON *all_rat = NULL;
    cJSON *freq = NULL;
    cJSON *rat_type = NULL;
    cJSON *svc_exp_threshold = NULL;
    cJSON *matching_dir = NULL;
    all_freq = cJSON_GetObjectItemCaseSensitive(rat_freq_informationJSON, "allFreq");
    if (all_freq) {
    if (!cJSON_IsBool(all_freq)) {
        ogs_error("OpenAPI_rat_freq_information_parseFromJSON() failed [all_freq]");
        goto end;
    }
    }

    all_rat = cJSON_GetObjectItemCaseSensitive(rat_freq_informationJSON, "allRat");
    if (all_rat) {
    if (!cJSON_IsBool(all_rat)) {
        ogs_error("OpenAPI_rat_freq_information_parseFromJSON() failed [all_rat]");
        goto end;
    }
    }

    freq = cJSON_GetObjectItemCaseSensitive(rat_freq_informationJSON, "freq");
    if (freq) {
    }

    rat_type = cJSON_GetObjectItemCaseSensitive(rat_freq_informationJSON, "ratType");
    if (rat_type) {
    }

    svc_exp_threshold = cJSON_GetObjectItemCaseSensitive(rat_freq_informationJSON, "svcExpThreshold");
    if (svc_exp_threshold) {
    }

    matching_dir = cJSON_GetObjectItemCaseSensitive(rat_freq_informationJSON, "matchingDir");
    if (matching_dir) {
    }

    rat_freq_information_local_var = OpenAPI_rat_freq_information_create (
        all_freq ? true : false,
        all_freq ? all_freq->valueint : 0,
        all_rat ? true : false,
        all_rat ? all_rat->valueint : 0,
    );

    return rat_freq_information_local_var;
end:
    return NULL;
}

OpenAPI_rat_freq_information_t *OpenAPI_rat_freq_information_copy(OpenAPI_rat_freq_information_t *dst, OpenAPI_rat_freq_information_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_rat_freq_information_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_rat_freq_information_convertToJSON() failed");
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

    OpenAPI_rat_freq_information_free(dst);
    dst = OpenAPI_rat_freq_information_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

