/* file      : libpq/pg_config.h -*- C -*-
 * license   : PostgreSQL License; see accompanying COPYRIGHT file
 */

/*
 * For the semantics of the following macros refer to pg_config.h.in.orig and
 * the upstream's configure.in.
 *
 * Note that we will explicitly undefine macros that are present in the libpq
 * source code but should not be defined. While this is not technically
 * required, it simplifies the change tracking (see README-DEV). As a bonus we
 * also make sure that they are not get eventually defined by some system
 * headers.
 */

#include <stddef.h> /* offsetof() */

#include <openssl/opensslv.h> /* OPENSSL_VERSION_NUMBER */

/*
 * Version.
 */
#undef   PG_VERSION
#undef   PG_VERSION_NUM
#undef   PG_MAJORVERSION
#include <libpq/version.h>

/*
 * Endianess.
 */
#ifdef __FreeBSD__
#  include <sys/endian.h> /* BYTE_ORDER */
#else
#  if defined(_WIN32)
#    ifndef BYTE_ORDER
#      define BIG_ENDIAN    4321
#      define LITTLE_ENDIAN 1234
#      define BYTE_ORDER    LITTLE_ENDIAN
#    endif
#  else
#    include <sys/param.h>  /* BYTE_ORDER/__BYTE_ORDER */
#    ifndef BYTE_ORDER
#      ifdef __BYTE_ORDER
#        define BYTE_ORDER    __BYTE_ORDER
#        define BIG_ENDIAN    __BIG_ENDIAN
#        define LITTLE_ENDIAN __LITTLE_ENDIAN
#      else
#        error no BYTE_ORDER/__BYTE_ORDER define
#      endif
#    endif
#  endif
#endif

#if BYTE_ORDER == BIG_ENDIAN
# define WORDS_BIGENDIAN 1
#endif

/*
 * Types, type sizes and alignments.
 */
#define ALIGNOF_(type) offsetof (struct {char c; type m;}, m)
#define ALIGNOF_DOUBLE ALIGNOF_ (double)
#define ALIGNOF_INT    ALIGNOF_ (int)
#define ALIGNOF_LONG   ALIGNOF_ (long)
#define ALIGNOF_SHORT  ALIGNOF_ (short)

/*
 * GCC and Clang provide __SIZEOF_*__ and  __*_TYPE__ predefined macros that we
 * use to define the required libpq macros. Note that on Windows long and
 * long long types are always of 32 and 64 bits width respectively.
 */
#ifndef _WIN32
#  if __SIZEOF_LONG__ == 8
#    define HAVE_LONG_INT_64       1
#  endif
#  ifdef __SIZEOF_LONG_LONG__
#    define HAVE_LONG_LONG_INT     1
#  endif
#  if __SIZEOF_LONG_LONG__ == 8
#    define HAVE_LONG_LONG_INT_64  1
#  endif
#  if __SIZEOF_LONG_LONG__ > __SIZEOF_DOUBLE__
#    define MAXIMUM_ALIGNOF        __SIZEOF_LONG_LONG__
#  else
#    define MAXIMUM_ALIGNOF        __SIZEOF_DOUBLE__
#  endif
#  ifdef __SIZEOF_INT128__
#    define PG_INT128_TYPE         __int128
#    define ALIGNOF_PG_INT128_TYPE 16
#  endif
#  define PG_INT64_TYPE            __INT64_TYPE__
#  define ACCEPT_TYPE_ARG3         socklen_t
#  define SIZEOF_SIZE_T            __SIZEOF_SIZE_T__
#  define SIZEOF_VOID_P            __SIZEOF_POINTER__
#else
#  define HAVE_LONG_LONG_INT       1
#  define HAVE_LONG_LONG_INT_64    1
#  define MAXIMUM_ALIGNOF          8
#  define PG_INT64_TYPE            long long int
#  define ACCEPT_TYPE_ARG3         int
#  ifdef _WIN64
#    define SIZEOF_SIZE_T          8
#    define SIZEOF_VOID_P          8
#  else
#    define SIZEOF_SIZE_T          4
#    define SIZEOF_VOID_P          4
#  endif
#endif

#define INT64_MODIFIER "ll"

/*
 * Specific for FreeBSD.
 */
#ifdef __FreeBSD__
#  define HAVE_STRUCT_CMSGCRED 1

/*
 * Note that upstream also defines this macro for newer glibc versions (see
 * buildfile for details).
 */
#  define HAVE_EXPLICIT_BZERO  1
#endif

/*
 * Specific for Mac OS.
 */
#ifdef __APPLE__
#  define HAVE_DECL_F_FULLFSYNC 1
#else
#  define HAVE_DECL_F_FULLFSYNC 0
#endif

/*
 * Specific for FreeBSD and Linux.
 */
#if defined(__FreeBSD__) || defined(__linux__)
#  define HAVE_STRCHRNUL 1
#endif

/*
 * Specific for FreeBSD and Mac OS.
 */
#if defined(__FreeBSD__) || defined(__APPLE__)
#  define HAVE_DECL_STRLCAT                   1
#  define HAVE_DECL_STRLCPY                   1
#  define STRERROR_R_INT                      1
#  define HAVE_FLS                            1
#  define HAVE_GETPEEREID                     1
#  define HAVE_STRTOQ                         1
#  define HAVE_STRTOUQ                        1
#  define HAVE_STRUCT_SOCKADDR_SA_LEN         1
#  define HAVE_STRUCT_SOCKADDR_STORAGE_SS_LEN 1
#  define HAVE_SYS_UCRED_H                    1
#  define HAVE_UNION_SEMUN                    1
#  define HAVE_MEMSET_S                       1
#else
#  define HAVE_DECL_STRLCAT                   0
#  define HAVE_DECL_STRLCPY                   0
#endif

/*
 * Specific for POSIX.
 */
#ifndef _WIN32
#  define HAVE_DECL_FDATASYNC     1
#  define HAVE_DECL_RTLD_GLOBAL   1
#  define HAVE_DECL_RTLD_NOW      1
#  define HAVE_FDATASYNC          1
#  define HAVE_GETADDRINFO        1
#  define HAVE_GETPWUID_R         1
#  define HAVE_INET_ATON          1
#  define HAVE_LANGINFO_H         1
#  define HAVE_MKDTEMP            1
#  define HAVE_NETINET_TCP_H      1
#  define HAVE_DECL_POSIX_FADVISE 1
#  define HAVE_POSIX_FADVISE      1
#  define HAVE_RANDOM             1
#  define HAVE_SRANDOM            1
#  define HAVE_STRERROR_R         1
#  define HAVE_STRINGS_H          1
#  define HAVE_POLL               1
#  define HAVE_POLL_H             1
#  define HAVE_SYS_SELECT_H       1
#  define HAVE_SYS_UN_H           1
#  define HAVE_TERMIOS_H          1
#  define HAVE_UNSETENV           1
#  define HAVE_DLOPEN             1
#  define HAVE_PREAD              1
#  define HAVE_PWRITE             1
#  define HAVE_LINK               1
#  define HAVE_STRUCT_SOCKADDR_UN 1

/*
 * Specific for Windows.
 */
#else
#  define HAVE_DECL_FDATASYNC     0
#  define HAVE_DECL_RTLD_GLOBAL   0
#  define HAVE_DECL_RTLD_NOW      0
#  define HAVE_DECL_POSIX_FADVISE 0
#  define HAVE_FUNCNAME__FUNCTION 1

#  ifdef __MINGW32__
#    define HAVE_GETTIMEOFDAY     1
#  endif
#endif

/*
 * Specific for GNU C Library.
 */
#ifdef __GLIBC__
# define HAVE_GETHOSTBYNAME_R 1
#endif

/*
 * Specific for (non-) VC.
 */
#ifndef _MSC_VER
#  define HAVE__BUILTIN_TYPES_COMPATIBLE_P 1
#  define HAVE__BUILTIN_UNREACHABLE        1
#  define HAVE__BUILTIN_BSWAP16            1
#  define HAVE__BUILTIN_BSWAP32            1
#  define HAVE__BUILTIN_BSWAP64            1
#  define HAVE__BUILTIN_OP_OVERFLOW        1
#  define HAVE_SETENV                      1

/*
 * _Static_assert() was introduced in C11. However, all the latest major
 * compilers, except for MSVC, support it for C99 as well.
 */
#  define HAVE__STATIC_ASSERT 1
#endif

/*
 * Relates to the enabled OpenSSL.
 */
#define USE_OPENSSL                   1
#define HAVE_OPENSSL_INIT_SSL         1
#define HAVE_ASN1_STRING_GET0_DATA    1
#define HAVE_BIO_GET_DATA             1
#define HAVE_BIO_METH_NEW             1

#if OPENSSL_VERSION_NUMBER >= 0x10100000L
#  define HAVE_HMAC_CTX_FREE          1
#  define HAVE_HMAC_CTX_NEW           1
#else
#  define HAVE_CRYPTO_LOCK            1
#endif

#if OPENSSL_VERSION_NUMBER >= 0x10002000L
#  define HAVE_X509_GET_SIGNATURE_NID 1
#endif

/*
 * Common for all supported OSes/compilers.
 */
#define ENABLE_THREAD_SAFETY                   1
#define PG_USE_STDBOOL                         1
#define HAVE_DECL_STRNLEN                      1
#define HAVE_DECL_STRTOLL                      1
#define HAVE_DECL_STRTOULL                     1
#define HAVE_FUNCNAME__FUNC                    1
#define HAVE_IPV6                              1
#define HAVE_STRTOLL                           1
#define HAVE_STRTOULL                          1
#define HAVE_STRTOF                            1
#define HAVE_STRUCT_ADDRINFO                   1
#define HAVE_STRUCT_SOCKADDR_STORAGE           1
#define HAVE_STRUCT_SOCKADDR_STORAGE_SS_FAMILY 1
#define BLCKSZ                                 8192
#define XLOG_BLCKSZ                            8192
#define PG_KRB_SRVNAM                          "postgres"
#define PG_PRINTF_ATTRIBUTE                    printf
#define MEMSET_LOOP_LIMIT                      1024
#define DEF_PGPORT                             5432
#define DEF_PGPORT_STR                         "5432"

/*
 * Undefined macros.
 */

/*
 * The following features are disabled.
 */
#undef USE_ASSERT_CHECKING
#undef ENABLE_NLS
#undef ENABLE_GSS
#undef USE_LDAP

/*
 * Is meaningless if NLS support is disabled (see above and libpq/buildfile for
 * details).
 */
#undef LOCALEDIR

/*
 * Is meaningless if GSSAPI support is disabled (see above). It also seems that
 * for modern systems including <gssapi.h> or <gssapi/gssapi.h> will work both
 * (<gssapi.h> just includes <gssapi/gssapi.h>).
 */
#undef HAVE_GSSAPI_H

/*
 * Windows-specific. <crtdefs.h> is included for the latest (>= 1400) VC
 * unconditionally.
 */
#undef HAVE_CRTDEFS_H

/*
 * Solaris-specific (getpeerucred() function).
 */
#undef HAVE_GETPEERUCRED

/*
 * Hard to even find any records of these types.
 */
#undef HAVE_INT64
#undef HAVE_INT8
#undef HAVE_UINT64
#undef HAVE_UINT8

/*
 * Something optimization-related for PowerPC machines (see
 * libpq/include/pg_config_manual.h for more details).
 */
#undef HAVE_PPC_LWARX_MUTEX_HINT

/*
 * None of the supported platforms has the '__' prefix for the mentioned
 * sockaddr_storage struct members.
 */
#undef HAVE_STRUCT_SOCKADDR_STORAGE___SS_FAMILY
#undef HAVE_STRUCT_SOCKADDR_STORAGE___SS_LEN

/*
 * Let's follow Linux man page advise for sync_file_range() function:
 *
 * This system call is Linux-specific, and should be avoided in portable
 * programs.
 *
 * The macro also seems to be backend-specific.
 */
#undef HAVE_SYNC_FILE_RANGE

/*
 * None of the supported OSes have <ucred.h>. FreeBSD and Mac OS have
 * <sys/ucred.h> (HAVE_SYS_UCRED_H macro).
 */
#undef HAVE_UCRED_H

/*
 * Meaningless as HAVE_STRTOULL and HAVE_STRTOULL are always defined.
 */
#undef HAVE___STRTOLL
#undef HAVE___STRTOULL

#define pg_restrict __restrict
