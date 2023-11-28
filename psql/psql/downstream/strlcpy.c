/* file      : psql/downstream/strlcpy.c -*- C -*-
 * license   : PostgreSQL License; see accompanying COPYRIGHT file
 */
#if !HAVE_DECL_STRLCPY
# include <src/port/strlcpy.c>
#endif
