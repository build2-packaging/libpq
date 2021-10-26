/* file      : tests/conninfo/postgres_fe.h
 * license   : PostgreSQL License; see accompanying COPYRIGHT file
 */

/* The upstream's uri-regress.c includes src/include/postgres_fe.h that is
 * located in libpq/include/ in our source tree. This file is not installed,
 * so to keep the test as a subproject and be able to test against the
 * installed libpq library we replace it with the header stub, containing the
 * bare minimum that is required the test to compile.
 */
#ifndef TESTS_CONNINFO_POSTGRES_FE_H
#define TESTS_CONNINFO_POSTGRES_FE_H

#include <stdbool.h>
#include <string.h>

#endif /* TESTS_CONNINFO_POSTGRES_FE_H */
