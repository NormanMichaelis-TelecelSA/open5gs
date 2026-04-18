/*
 * threshold_level.h
 *
 * Represents a threshold level.
 */

#ifndef _OpenAPI_threshold_level_H_
#define _OpenAPI_threshold_level_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_threshold_level_s OpenAPI_threshold_level_t;
typedef struct OpenAPI_threshold_level_s {
    bool is_cong_level;
    int cong_level;
    bool is_nf_load_level;
    int nf_load_level;
    bool is_nf_cpu_usage;
    int nf_cpu_usage;
    bool is_nf_memory_usage;
    int nf_memory_usage;
    bool is_nf_storage_usage;
    int nf_storage_usage;
} OpenAPI_threshold_level_t;

OpenAPI_threshold_level_t *OpenAPI_threshold_level_create(
    bool is_cong_level,
    int cong_level,
    bool is_nf_load_level,
    int nf_load_level,
    bool is_nf_cpu_usage,
    int nf_cpu_usage,
    bool is_nf_memory_usage,
    int nf_memory_usage,
    bool is_nf_storage_usage,
    int nf_storage_usage,
);
void OpenAPI_threshold_level_free(OpenAPI_threshold_level_t *threshold_level);
OpenAPI_threshold_level_t *OpenAPI_threshold_level_parseFromJSON(cJSON *threshold_levelJSON);
cJSON *OpenAPI_threshold_level_convertToJSON(OpenAPI_threshold_level_t *threshold_level);
OpenAPI_threshold_level_t *OpenAPI_threshold_level_copy(OpenAPI_threshold_level_t *dst, OpenAPI_threshold_level_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_threshold_level_H_ */

