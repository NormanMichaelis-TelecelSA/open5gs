/*
 * service_experience_info.h
 *
 * Represents service experience information.
 */

#ifndef _OpenAPI_service_experience_info_H_
#define _OpenAPI_service_experience_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "location_info.h"
#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_service_experience_info_s OpenAPI_service_experience_info_t;
typedef struct OpenAPI_service_experience_info_s {
    OpenAPI_list_t *supis;
    OpenAPI_list_t *ue_locs;
} OpenAPI_service_experience_info_t;

OpenAPI_service_experience_info_t *OpenAPI_service_experience_info_create(
    OpenAPI_list_t *supis,
    OpenAPI_list_t *ue_locs,
);
void OpenAPI_service_experience_info_free(OpenAPI_service_experience_info_t *service_experience_info);
OpenAPI_service_experience_info_t *OpenAPI_service_experience_info_parseFromJSON(cJSON *service_experience_infoJSON);
cJSON *OpenAPI_service_experience_info_convertToJSON(OpenAPI_service_experience_info_t *service_experience_info);
OpenAPI_service_experience_info_t *OpenAPI_service_experience_info_copy(OpenAPI_service_experience_info_t *dst, OpenAPI_service_experience_info_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_service_experience_info_H_ */

