#!/bin/sh
CURDIR=`pwd`
FP_DESKTOP=$CURDIR/../../../../fp_desktop
DEPS=$CURDIR/../../../target/dependencies
STAGING=$CURDIR/../../../target/staging
export LD_LIBRARY_PATH=$DEPS/linux-x64/lib:$STAGING
export FPDESKARGS="-w 800 -h 600 -r $CURDIR -p $DEPS/python/lib -p $DEPS/linux-x64/lib $CURDIR/fps.py"
valgrind --tool=memcheck --leak-check=yes $FP_DESKTOP/target/staging/fp_desktop $FPDESKARGS
