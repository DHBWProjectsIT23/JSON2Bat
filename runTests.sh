#!/bin/bash

# Define the directory containing JSON files
JSON_DIR="samples/tests"

# Define the path to the executable
EXECUTABLE="./build/Debug/json2batch"

# Check if the executable exists
if [ ! -x "$EXECUTABLE" ]; then
    echo "Error: Executable '$EXECUTABLE' not found or not executable."
    exit 1
fi

# Check if the directory containing JSON files exists
if [ ! -d "$JSON_DIR" ]; then
    echo "Error: Directory '$JSON_DIR' not found."
    exit 1
fi

# Change directory to the JSON directory
cd "$JSON_DIR" || exit

files=""
# Loop through each JSON file and parse it
for file in *.json; do
    echo "Adding file: ${JSON_DIR}/$file"
    files="${files} ${JSON_DIR}/${file}"
    echo "----------------------------------------"
done

cd -

"$EXECUTABLE" $files -o "samples/results"
