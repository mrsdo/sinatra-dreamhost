/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) 2007 Manlio Perillo (manlio.perillo@gmail.com)
 * Copyright (c) 2010-2017 Phusion Holding B.V.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _PASSENGER_NGINX_CONFIGURATION_H_
#define _PASSENGER_NGINX_CONFIGURATION_H_

#include <ngx_config.h>
#include <ngx_http.h>

#include "MainConfig/AutoGeneratedStruct.h"
#include "LocationConfig/AutoGeneratedStruct.h"

struct passenger_main_conf_s {
    passenger_autogenerated_main_conf_t autogenerated;
    ngx_str_t     default_ruby;
    PsgJsonValue *manifest;
};

struct passenger_loc_conf_s {
    passenger_autogenerated_loc_conf_t autogenerated;

    struct passenger_loc_conf_s *parent;
    ngx_array_t children;
    ngx_http_core_srv_conf_t *cscf;
    ngx_http_core_loc_conf_t *clcf;
    ngx_str_t context_source_file;
    ngx_uint_t context_source_line;

    ngx_http_upstream_conf_t upstream_config;
    ngx_array_t *flushes;
    ngx_array_t *headers_set_len;
    ngx_array_t *headers_set;
    ngx_hash_t   headers_set_hash;

    #if (NGX_HTTP_CACHE)
        ngx_http_complex_value_t cache_key;
    #endif

    /** Raw HTTP header data for this location are cached here. */
    ngx_str_t    options_cache;
    ngx_str_t    env_vars_cache;
};

#ifndef _PASSENGER_NGINX_MODULE_CONF_STRUCT_TYPEDEFS_H_
    #define _PASSENGER_NGINX_MODULE_CONF_STRUCT_TYPEDEFS_H_
    struct passenger_main_conf_s;
    struct passenger_loc_conf_s;
    typedef struct passenger_main_conf_s passenger_main_conf_t;
    typedef struct passenger_loc_conf_s passenger_loc_conf_t;
#endif /* _PASSENGER_NGINX_MODULE_CONF_STRUCT_TYPEDEFS_H_ */

extern const ngx_command_t   passenger_commands[];
extern passenger_main_conf_t passenger_main_conf;

void *passenger_create_main_conf(ngx_conf_t *cf);
char *passenger_init_main_conf(ngx_conf_t *cf, void *conf_pointer);
void *passenger_create_loc_conf(ngx_conf_t *cf);
char *passenger_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child);
ngx_int_t passenger_postprocess_config(ngx_conf_t *cf);

PsgJsonValue *psg_json_value_set_str_array(PsgJsonValue *doc, const char *name, ngx_array_t *ary);
PsgJsonValue *psg_json_value_set_str_keyval(PsgJsonValue *doc, const char *name, ngx_array_t *ary);

#endif /* _PASSENGER_NGINX_CONFIGURATION_H_ */
