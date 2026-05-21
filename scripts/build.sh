#!/bin/bash
set -e

premake5 gmake

if [[ $* == *--export-compile-commands* ]]; then
    bear -- make -C build/
else
    make -C build/
fi
