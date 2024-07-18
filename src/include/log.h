// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <slog.h>

#ifdef __cplusplus
extern "C" {
#endif

int vaccel_log_init(void);
int vaccel_log_shutdown(void);

#define vaccel_info slog_info
#define vaccel_warn slog_warn
#define vaccel_debug slog_debug
#define vaccel_error slog_error
#define vaccel_trace slog_trace
#define vaccel_fatal slog_fatal

#define vaccel_prof_info(fmt, ...) do { \
    char buffer[1024]; \
    snprintf(buffer, sizeof(buffer), fmt, __VA_ARGS__); \
    slog_info("%s", buffer); \
    write_prof_output_to_file(buffer); \
} while (0)

#ifdef __cplusplus
}
#endif
