#!/bin/bash

# Check if the correct number of command line arguments is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <input_prefix>"
    exit 1
fi

# Input prefix (e.g., "test")
input_prefix="$1"
graph_file="$input_prefix.graph"
satoutput_file="$input_prefix.satoutput"
mapping_file="$input_prefix.mapping"

# Check if the SAT output file and graph file exist
if [ ! -f "$satoutput_file" ] || [ ! -f "$graph_file" ]; then
    echo "SAT output file '$satoutput_file' or '$graph_file' not found."
    exit 1
fi

# generate the mapping file
g++ ai_out.cpp -o output_graphs
./output_graphs $graph_file $satoutput_file $mapping_file 1

echo "Mapping file '$mapping_file' generated."
