/*
 * node_functionality_any_of.h
 *
 * 
 */

#ifndef _OpenAPI_node_functionality_any_of_H_
#define _OpenAPI_node_functionality_any_of_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_node_functionality_any_of_NULL = 0, OpenAPI_node_functionality_any_of_SMF, OpenAPI_node_functionality_any_of_SMSF, OpenAPI_node_functionality_any_of_I_SMF } OpenAPI_node_functionality_any_of_e;

char* OpenAPI_node_functionality_any_of_ToString(OpenAPI_node_functionality_any_of_e node_functionality_any_of);

OpenAPI_node_functionality_any_of_e OpenAPI_node_functionality_any_of_FromString(char* node_functionality_any_of);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_node_functionality_any_of_H_ */

