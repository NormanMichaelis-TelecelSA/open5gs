/*
 * _chargingdata_post_400_response.h
 *
 * 
 */

#ifndef _OpenAPI__chargingdata_post_400_response_H_
#define _OpenAPI__chargingdata_post_400_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "charging_notify_response.h"
#include "invalid_param.h"
#include "invocation_result.h"
#include "object.h"
#include "problem_details.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI__chargingdata_post_400_response_s OpenAPI__chargingdata_post_400_response_t;
typedef struct OpenAPI__chargingdata_post_400_response_s {
    char *title;
    bool is_status;
    int status;
    char *detail;
    char *cause;
    OpenAPI_list_t *invalid_params;
    struct OpenAPI_invocation_result_s *invocation_result;
} OpenAPI__chargingdata_post_400_response_t;

OpenAPI__chargingdata_post_400_response_t *OpenAPI__chargingdata_post_400_response_create(
    char *title,
    bool is_status,
    int status,
    char *detail,
    char *cause,
    OpenAPI_list_t *invalid_params,
    OpenAPI_invocation_result_t *invocation_result
);
void OpenAPI__chargingdata_post_400_response_free(OpenAPI__chargingdata_post_400_response_t *_chargingdata_post_400_response);
OpenAPI__chargingdata_post_400_response_t *OpenAPI__chargingdata_post_400_response_parseFromJSON(cJSON *_chargingdata_post_400_responseJSON);
cJSON *OpenAPI__chargingdata_post_400_response_convertToJSON(OpenAPI__chargingdata_post_400_response_t *_chargingdata_post_400_response);
OpenAPI__chargingdata_post_400_response_t *OpenAPI__chargingdata_post_400_response_copy(OpenAPI__chargingdata_post_400_response_t *dst, OpenAPI__chargingdata_post_400_response_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI__chargingdata_post_400_response_H_ */

