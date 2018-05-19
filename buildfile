# file      : buildfile
# copyright : Copyright (c) 2016-2017 Code Synthesis Ltd
# license   : PostgreSQL License; see accompanying COPYRIGHT file

./: {*/ -build/} doc{COPYRIGHT INSTALL README} manifest

# Don't install tests or the INSTALL file.
#
dir{tests/}:     install = false
doc{INSTALL}@./: install = false
