#!/bin/bash

# Config respectively
folder_name="Sprint4"
autotester_path="../Code10/build/src/autotester/autotester"

# Exit on error
set -e

# Clear the output folder before each run
rm -rf output/*.xml

# Fetch all source files in the sources folder
source_folder="${folder_name}/sources"
source_files=("${source_folder}"/*.txt)

# Iterate through source files
for source_file in "${source_files[@]}"; do
    # Extract source name without extension
    source_name=$(basename -- "${source_file%.*}")

    # Find corresponding query files in the queries/source/ folder
    query_folder="${folder_name}/queries"
    query_files=("${query_folder}/${source_name}"/*.txt)

    # Iterate through query files
    for query_file in "${query_files[@]}"; do
        # Extract query name without extension
        query_name=$(basename -- "${query_file%.*}")

        output_file="output/out_${source_name}_${query_name}.xml"

        "${autotester_path}" "$source_file" "$query_file" "$output_file"
    done
done

# Exit successfully
exit 0