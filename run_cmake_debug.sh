#!/bin/bash

cmake --build ./generated/build-debug
echo "[SCRIPT] rapidjson-learning started"
./generated/build-debug/bin/rapidjson-learning
echo "[SCRIPT] rapidjson-learning ended"