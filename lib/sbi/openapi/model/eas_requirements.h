/*
 * eas_requirements.h
 *
 * 
 */

#ifndef _OpenAPI_eas_requirements_H_
#define _OpenAPI_eas_requirements_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_eas_requirements_s OpenAPI_eas_requirements_t;
typedef struct OpenAPI_eas_requirements_s {
    bool is_service_continuity;
    int service_continuity;
} OpenAPI_eas_requirements_t;

OpenAPI_eas_requirements_t *OpenAPI_eas_requirements_create(
    bool is_service_continuity,
    int service_continuity
);
void OpenAPI_eas_requirements_free(OpenAPI_eas_requirements_t *eas_requirements);
OpenAPI_eas_requirements_t *OpenAPI_eas_requirements_parseFromJSON(cJSON *eas_requirementsJSON);
cJSON *OpenAPI_eas_requirements_convertToJSON(OpenAPI_eas_requirements_t *eas_requirements);
OpenAPI_eas_requirements_t *OpenAPI_eas_requirements_copy(OpenAPI_eas_requirements_t *dst, OpenAPI_eas_requirements_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_eas_requirements_H_ */

