/*
 * charging_data_request.h
 *
 * 
 */

#ifndef _OpenAPI_charging_data_request_H_
#define _OpenAPI_charging_data_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "multiple_unit_usage.h"
#include "nf_identification.h"
#include "pdu_session_charging_information.h"
#include "roaming_qbc_information.h"
#include "trigger.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_charging_data_request_s OpenAPI_charging_data_request_t;
typedef struct OpenAPI_charging_data_request_s {
    char *subscriber_identifier;
    struct OpenAPI_nf_identification_s *nf_consumer_identification;
    char *invocation_time_stamp;
    int invocation_sequence_number;
    bool is_retransmission_indicator;
    int retransmission_indicator;
    char *service_specification_info;
    OpenAPI_list_t *multiple_unit_usage;
    OpenAPI_list_t *triggers;
    struct OpenAPI_pdu_session_charging_information_s *p_du_session_charging_information;
    struct OpenAPI_roaming_qbc_information_s *roaming_qbc_information;
} OpenAPI_charging_data_request_t;

OpenAPI_charging_data_request_t *OpenAPI_charging_data_request_create(
    char *subscriber_identifier,
    OpenAPI_nf_identification_t *nf_consumer_identification,
    char *invocation_time_stamp,
    int invocation_sequence_number,
    bool is_retransmission_indicator,
    int retransmission_indicator,
    char *service_specification_info,
    OpenAPI_list_t *multiple_unit_usage,
    OpenAPI_list_t *triggers,
    OpenAPI_pdu_session_charging_information_t *p_du_session_charging_information,
    OpenAPI_roaming_qbc_information_t *roaming_qbc_information
);
void OpenAPI_charging_data_request_free(OpenAPI_charging_data_request_t *charging_data_request);
OpenAPI_charging_data_request_t *OpenAPI_charging_data_request_parseFromJSON(cJSON *charging_data_requestJSON);
cJSON *OpenAPI_charging_data_request_convertToJSON(OpenAPI_charging_data_request_t *charging_data_request);
OpenAPI_charging_data_request_t *OpenAPI_charging_data_request_copy(OpenAPI_charging_data_request_t *dst, OpenAPI_charging_data_request_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_charging_data_request_H_ */

