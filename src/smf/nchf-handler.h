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

#ifndef SMF_NCHF_HANDLER_H
#define SMF_NCHF_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "context.h"

bool smf_nchf_convergedcharging_handle_create(
        smf_sess_t *sess, ogs_sbi_stream_t *stream,
        ogs_sbi_message_t *recvmsg);
bool smf_nchf_convergedcharging_handle_update(
        smf_sess_t *sess, ogs_sbi_stream_t *stream,
        ogs_sbi_message_t *recvmsg);
bool smf_nchf_convergedcharging_handle_release(
        smf_sess_t *sess, ogs_sbi_stream_t *stream,
        ogs_sbi_message_t *recvmsg);

#ifdef __cplusplus
}
#endif

#endif /* SMF_NCHF_HANDLER_H */
