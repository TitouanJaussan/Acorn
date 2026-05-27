#!/bin/bash
set -e

premake5 gmake

if [[ $* == *--export-compile-commands* ]]; then
    bear -- make -C build/ -j 4
else
    make -C build/ -j 4
fi
