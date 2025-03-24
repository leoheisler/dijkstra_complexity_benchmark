#!/bin/bash

# Pasta específica
dir="./graphs"

# Itera sobre cada arquivo encontrado na pasta (recursivamente)
while IFS= read -r graph_file; do
    echo $graph_file
    ./build/dijk "?" "?" < $graph_file
    echo "-----------------------------"
done < <(find "$dir" -type f)
