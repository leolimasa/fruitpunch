#!/bin/sh
CURDIR=`pwd`
FP_DESKTOP=$CURDIR/../../../fp_desktop
DEPS=$CURDIR/../../target/dependencies
STAGING=$CURDIR/../../target/staging
FPPY=$CURDIR/../main
export LD_LIBRARY_PATH=$DEPS/linux-x64/lib:$STAGING
export FPDESKARGS="-w 800 -h 600 -r $CURDIR/../resources -p $FPPY  -p $DEPS/python/lib -p $DEPS/linux-x64/lib $CURDIR/physics.py"
valgrind --leak-check=yes $FP_DESKTOP/target/staging/fp_desktop $FPDESKARGS
