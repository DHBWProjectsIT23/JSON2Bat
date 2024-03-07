#!/bin/bash

echo "Building!"

cmake --build build/Debug
clear
./jsonToBatch
