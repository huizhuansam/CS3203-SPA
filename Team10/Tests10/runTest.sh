#!/bin/bash

# Config respectively
folder_name="Sprint5"
autotester_path_windows="../Code10/build/x64-Debug/src/autotester/autotester.exe"
autotester_path_mac_linux="../Code10/cmake-build-debug/src/autotester/autotester"

# Function to open a URL based on the operating system
open_url() {
    case "$OSTYPE" in
        "linux-gnu")
            xdg-open "$1"
            ;;
        "darwin"*)
            open "$1"
            ;;
        "cygwin" | "msys")
            start "" "$1"
            ;;
        *)
            echo "Unsupported operating system"
            ;;
    esac
}
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

        output_file="output/${source_name}____${query_name}.xml"

        case "$OSTYPE" in
        "linux-gnu")
            "${autotester_path_mac_linux}" "$source_file" "$query_file" "$output_file"
            ;;
        "darwin"*)
            "${autotester_path_mac_linux}" "$source_file" "$query_file" "$output_file"
            ;;
        "cygwin" | "msys")
            "${autotester_path_windows}" "$source_file" "$query_file" "$output_file"
            ;;
        *)
            echo "Unsupported operating system"
            ;;
        esac
    done
done

cd output

# Kill Python server to free up the port
PID=$( lsof -i:8000 -t )
if [ ! -z "$PID" ]
then
  echo "Killing process on port 8000"
  kill -9 $PID
fi


# Start Python HTTP server
python3 -m http.server 8000 &

failed=false
# Open .xml files that fail in the default browser
for xml_file in *.xml; do
    if grep -q "<failed>" "$xml_file" || grep -q "<timeout/>" "$xml_file"; then
        echo "Opening browser for: $xml_file"
        open_url "http://localhost:8000/$(basename "$xml_file")"
        failed=true
    fi
done

if [ "$failed" = false ]; then
    echo "***************************************************"
    echo "***************ALL TEST CASES PASSED***************"
    echo "***************************************************"
fi
