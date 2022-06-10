#!/bin/bash

set -e

mkdir `pwd`/build
rm -rf `pwd`/build/*
cd `pwd`/build &&
    cmake .. &&
    make
cd ..
cp -r `pwd`/include `pwd`/lib
