#!/bin/bash

cmake --build ./generated/build-release
echo "[SCRIPT] rapidjson-learning started"
./generated/build-release/bin/rapidjson-learning
echo "[SCRIPT] rapidjson-learning ended"