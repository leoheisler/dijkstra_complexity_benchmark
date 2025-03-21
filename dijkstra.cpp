#include "_Read.h"
#include "_Heap.h"
#include <cassert>
#include <climits>


std::vector<unsigned> dijkstra(int k, int num_vertices, Graph& g, unsigned source_index){
    std::vector<unsigned> dist(num_vertices, INT_MAX); 
    dist[source_index] = 0;

    //insert source node
    Heap kHeap(k);
    kHeap.insert(0, source_index);

    while (!kHeap.is_empty()) {
        Heap::Node heap_head = kHeap.extract_min();

        //get heap_neighbors, if distance is less than previously saved
        //update distance and insert neighbor in heap
        for (Graph::Edge edge : g.get_neighbors(heap_head.vertex)) {
            if (heap_head.distance + edge.weight < dist[edge.target]) {
                dist[edge.target] = dist[heap_head.vertex] + edge.weight;
                kHeap.insert(dist[edge.target], edge.target);
            }
        }
    }

    return dist;
}

int main(int argc, char* argv[]){
    assert(argc == 3);
    unsigned vertex_num = 0, edges_num = 0;
    unsigned source_index = std::stoi(argv[1]);
    unsigned target_index = std::stoi(argv[2]);
    Graph g;
    Read::read_dimacs(std::cin, vertex_num, edges_num, g);
    std::vector<unsigned> distances = dijkstra(2,vertex_num,g,source_index);

    return distances[target_index];
}