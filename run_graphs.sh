#!/bin/bash

# Pasta específica
dir="./graphs"

# Itera sobre cada arquivo encontrado na pasta (recursivamente)
while IFS= read -r graph_file; do
    ./build/dijk "?" "?" < $graph_file
done < <(find "$dir" -type f)
