/*
 * Copyright (c) 2017 Ichito Nagata, Fastly, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#ifndef h2o__http2client_h
#define h2o__http2client_h

#ifdef __cplusplus
extern "C" {
#endif

#include "h2o/memory.h"
#include "h2o/socket.h"
#include "h2o/socketpool.h"
#include "h2o/timeout.h"
#include "h2o/cache.h"

struct st_h2o_header_t;

typedef int (*h2o_http2client_body_cb)(h2o_http1client_t *client, const char *errstr);
typedef h2o_http2client_body_cb (*h2o_http2client_head_cb)(h2o_http1client_t *client, const char *errstr, int minor_version,
                                                           int status, h2o_iovec_t msg, struct st_h2o_header_t *headers,
                                                           size_t num_headers, int rlen);
typedef h2o_http2client_head_cb (*h2o_http2client_connect_cb)(h2o_http1client_t *client, const char *errstr, h2o_iovec_t *method, h2o_url_t *url,
                                                              struct st_h2o_header_t **headers, size_t *num_headers, h2o_iovec_t **bodies, size_t *num_bodies,
                                                              int *body_is_chunked, h2o_url_t *origin);


void h2o_http2client_connect(h2o_http1client_t **client, void *data, h2o_http1client_ctx_t *ctx, h2o_socketpool_t *socketpool,
                             h2o_url_t *target, h2o_http2client_connect_cb cb);
void h2o_http2client_cancel(h2o_http1client_t *client);

#ifdef __cplusplus
}
#endif

#endif