/*
 * service_area_restriction.h
 *
 * Provides information about allowed or not allowed areas.
 */

#ifndef _OpenAPI_service_area_restriction_H_
#define _OpenAPI_service_area_restriction_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "area.h"
#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_service_area_restriction_s OpenAPI_service_area_restriction_t;
typedef struct OpenAPI_service_area_restriction_s {
    OpenAPI_list_t *areas;
} OpenAPI_service_area_restriction_t;

OpenAPI_service_area_restriction_t *OpenAPI_service_area_restriction_create(
    OpenAPI_list_t *areas,
);
void OpenAPI_service_area_restriction_free(OpenAPI_service_area_restriction_t *service_area_restriction);
OpenAPI_service_area_restriction_t *OpenAPI_service_area_restriction_parseFromJSON(cJSON *service_area_restrictionJSON);
cJSON *OpenAPI_service_area_restriction_convertToJSON(OpenAPI_service_area_restriction_t *service_area_restriction);
OpenAPI_service_area_restriction_t *OpenAPI_service_area_restriction_copy(OpenAPI_service_area_restriction_t *dst, OpenAPI_service_area_restriction_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_service_area_restriction_H_ */

