/* file      : libpq/pg_config_paths.h -*- C -*-
 * copyright : Copyright (c) 2016-2019 Code Synthesis Ltd
 * license   : PostgreSQL License; see accompanying COPYRIGHT file
 */

/*
 * The upstream package makefile creates this file on the fly, dumping a
 * number of macro definitions. The libpq source files only use the SYSCONFDIR
 * macro (for the configuration we package against) which we define via the -D
 * preprocessor option (see buildfile for details).
 */
