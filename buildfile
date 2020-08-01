# file      : buildfile
# license   : PostgreSQL License; see accompanying COPYRIGHT file

# Glue buildfile that "pulls" all the packages.

import pkgs = {*/ -upstream/}
./: $pkgs
