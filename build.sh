#!/usr/bin/env bash

if [[ $# -eq 0 ]]
then
    cmake -B build
    cmake --build build --config Release
elif [[ $1 == "test" ]]
then
    cmake -B build
    cmake --build build --config Debug
    build/test/unit_tests
    gcovr build/test -e test
elif [[ $1 == "clean" ]]
then
    rm -rf build
fi