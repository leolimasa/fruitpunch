#!/bin/bash

# DIRS
CURDIR=`pwd`
TARGET=`readlink -f $CURDIR/../../target`
BASEDIR=`readlink -f $CURDIR/../../`
STAGINGDIR=$TARGET/staging
STAGINGTESTDIR=$TARGET/staging-test

rm -rf $STAGINGDIR
rm -rf $STAGINGTESTDIR
