/*
 * Copyright (C) 2019-2025 by Sukchan Lee <acetcom@gmail.com>
 * Copyright (C) 2026 by Phoenix SI (Pty) Ltd
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SMF_NCHF_OFFLINE_BUILD_H
#define SMF_NCHF_OFFLINE_BUILD_H

#include "context.h"

#ifdef __cplusplus
extern "C" {
#endif

/* TS 32.291 resource name for Nchf_OfflineOnlyCharging */
#define OGS_SBI_RESOURCE_NAME_OFFLINE_CHARGING_DATA "offlinechargingdata"

ogs_sbi_request_t *smf_nchf_offlineonlycharging_build_create(
        smf_sess_t *sess, void *data);
ogs_sbi_request_t *smf_nchf_offlineonlycharging_build_update(
        smf_sess_t *sess, void *data);
ogs_sbi_request_t *smf_nchf_offlineonlycharging_build_release(
        smf_sess_t *sess, void *data);

#ifdef __cplusplus
}
#endif

#endif /* SMF_NCHF_OFFLINE_BUILD_H */
