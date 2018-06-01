# file      : buildfile
# copyright : Copyright (c) 2016-2018 Code Synthesis Ltd
# license   : PostgreSQL License; see accompanying COPYRIGHT file

./: {*/ -build/} doc{COPYRIGHT INSTALL README} manifest

# Don't install tests or the INSTALL file.
#
tests/:          install = false
doc{INSTALL}@./: install = false
