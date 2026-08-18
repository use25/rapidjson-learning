#!/bin/bash

cmake -B ./generated/build-debug -DCMAKE_BUILD_TYPE=Debug
cmake -B ./generated/build-release -DCMAKE_BUILD_TYPE=Release