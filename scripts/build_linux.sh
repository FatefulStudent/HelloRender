#!/bin/bash
cd ..
clang-format -verbose -i src/*
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -s
