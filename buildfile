# file      : buildfile
# copyright : Copyright (c) 2016-2017 Code Synthesis Ltd
# license   : PostgreSQL License; see accompanying COPYRIGHT file

./: {*/ -build/} doc{COPYRIGHT INSTALL README version} file{manifest}

# The version file is auto-generated (by the version module) from manifest.
# Include it in distribution and don't remove when cleaning in src (so that
# clean results in a state identical to distributed).
#
doc{version}: file{manifest}
doc{version}: dist  = true
doc{version}: clean = ($src_root != $out_root)

# Don't install tests or the INSTALL file.
#
dir{tests/}:     install = false
doc{INSTALL}@./: install = false
