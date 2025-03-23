#!/bin/bash

vertex_num=12000
graph_prefix="graphs/"
prob=0

echo "0.01/0.02/0.03/0.04"
# fixed vertex graphs 12000 with low num of edges
for i in {1..4}; do
    prob=$(echo "$prob + 0.01" | bc)
    prob_int=$(echo "$prob * 100" | bc)
    graph_name="${graph_prefix}${vertex_num}_${prob_int}.gr"
    ./build/gen "$vertex_num" "$prob" "$graph_name"

    sleep 1
done

prob=0

echo "0.025/0.05/0.075/0.1"

# fixed vertex graphs 12000 with medium num of edges
for i in {1..4}; do
    prob=$(echo "$prob + 0.025" | bc)
    prob_int=$(echo "$prob * 100" | bc)
    graph_name="${graph_prefix}${vertex_num}_${prob_int}.gr"
    ./build/gen "$vertex_num" "$prob" "$graph_name"

    sleep 1
done

prob=0.1

echo "0.15/0.2/0.25"
# fixed vertex graphs 12000 with high num of edges
for i in {1..3}; do
    prob=$(echo "$prob + 0.5" | bc)
    prob_int=$(echo "$prob * 100 / 1" | bc)
    graph_name="${graph_prefix}${vertex_num}_${prob_int}.gr"
    ./build/gen "$vertex_num" "$prob" "$graph_name"

    sleep 1
done


#starts building graphs with fixed num of edges and vary in vertexes
echo "starting now fixed edges 750.000"
echo "5.000/6.000/7.000/8.000 - low number of vertexes"
edges_num=750000
vertex_num=4000
for i in {1..4}; do
    # Incrementa o número de vértices
    vertex_num=$(echo "$vertex_num + 1000" | bc)
    prob=$(echo "scale=5; $edges_num / ($vertex_num * $vertex_num)" | bc -l)
    graph_name="${graph_prefix}${vertex_num}_${edges_num}.gr"
    
    ./build/gen "$vertex_num" "$prob" "$graph_name"
    
    sleep 1
done

echo "10.000/12.500/15.000 - medium number of vertexes"

vertex_num=7500
for i in {1..3}; do
    # Incrementa o número de vértices
    vertex_num=$(echo "$vertex_num + 2500" | bc)
    prob=$(echo "scale=5; $edges_num / ($vertex_num * $vertex_num)" | bc -l)
    graph_name="${graph_prefix}${vertex_num}_${edges_num}.gr"
    
    ./build/gen "$vertex_num" "$prob" "$graph_name"
    
    sleep 1
done

echo "20.000/25.000/30.000 - high number of vertexes"
vertex_num=15000
for i in {1..3}; do
    # Incrementa o número de vértices
    vertex_num=$(echo "$vertex_num + 5000" | bc)
    prob=$(echo "scale=5; $edges_num / ($vertex_num * $vertex_num)" | bc -l)
    graph_name="${graph_prefix}${vertex_num}_${edges_num}.gr"
    
    ./build/gen "$vertex_num" "$prob" "$graph_name"
    
    sleep 1
done
