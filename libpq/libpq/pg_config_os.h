/* file      : libpq/pg_config_os.h -*- C -*-
 * license   : PostgreSQL License; see accompanying COPYRIGHT file
 */

/*
 * The upstream package makefile creates this file as a symlink to the
 * target-specific header in src/include/port/.
 */

#if defined(__linux__)
#  include <include/port/linux.h>
#elif defined(__FreeBSD__)
#  include <include/port/freebsd.h>
#elif defined(__APPLE__)
#  include <include/port/darwin.h>
#elif defined(_WIN32)
#  include <include/port/win32.h>
#else
#  error this OS is not supported
#endif
