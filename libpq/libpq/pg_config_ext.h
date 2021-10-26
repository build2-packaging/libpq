/* file      : libpq/pg_config_ext.h -*- C -*-
 * license   : PostgreSQL License; see accompanying COPYRIGHT file
 */

/*
 * For the semantics of the following macros refer to pg_config_ext.h.in.orig
 * and the upstream's configure.in.
 */

/*
 * Note that <stdint.h> is invented by C99 and we can't expect that the libpq
 * client is compiled according to this standard. However, when compile with
 * GCC, Clang or VC, even requesting C90 standard explicitly, then the header
 * and int64_t type are both available.
 */
#include <stdint.h>

#define PG_INT64_TYPE int64_t
