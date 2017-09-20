/* file      : libpq/postgresql/pg_config_ext.h -*- C -*-
 * copyright : Copyright (c) 2016-2017 Code Synthesis Ltd
 * license   : PostgreSQL License; see accompanying COPYRIGHT file
 */

/*
 * For the semanics of the following macros refer to the
 * libpq/postgresql/pg_config_ext.h.in.orig and
 * libpq/postgresql/pg_config_ext.h.win32.orig file.
 */

/*
 * Note that <stdint.h> is invented by C99 and we can't expect that the libpq
 * client is compiled according to this standard. However, when compile with
 * GCC, Clang or VC, even requesting C90 standard explicitly, then the header
 * and int64_t type are both available.
 */
#include <stdint.h>

#define PG_INT64_TYPE int64_t
