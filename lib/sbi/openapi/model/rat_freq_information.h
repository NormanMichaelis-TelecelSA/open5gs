/*
 * rat_freq_information.h
 *
 * Represents the RAT type and/or Frequency information.
 */

#ifndef _OpenAPI_rat_freq_information_H_
#define _OpenAPI_rat_freq_information_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_rat_freq_information_s OpenAPI_rat_freq_information_t;
typedef struct OpenAPI_rat_freq_information_s {
    bool is_all_freq;
    int all_freq;
    bool is_all_rat;
    int all_rat;
} OpenAPI_rat_freq_information_t;

OpenAPI_rat_freq_information_t *OpenAPI_rat_freq_information_create(
    bool is_all_freq,
    int all_freq,
    bool is_all_rat,
    int all_rat,
);
void OpenAPI_rat_freq_information_free(OpenAPI_rat_freq_information_t *rat_freq_information);
OpenAPI_rat_freq_information_t *OpenAPI_rat_freq_information_parseFromJSON(cJSON *rat_freq_informationJSON);
cJSON *OpenAPI_rat_freq_information_convertToJSON(OpenAPI_rat_freq_information_t *rat_freq_information);
OpenAPI_rat_freq_information_t *OpenAPI_rat_freq_information_copy(OpenAPI_rat_freq_information_t *dst, OpenAPI_rat_freq_information_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_rat_freq_information_H_ */

