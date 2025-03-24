#include "_Read.h"
#include "_Heap.h"
#include <cassert>
#include <climits>
#include <fstream>


std::vector<unsigned> dijkstra(int k, int num_vertices, Graph& g, unsigned source_index){

    //set outfile
    std::ofstream outfile("results.txt",std::ios::app);
    if (!outfile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
        exit;
    }

    //start funct
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
                dist[edge.target] = heap_head.distance + edge.weight;
                kHeap.insert(dist[edge.target], edge.target);
            }
        }
    }
    outfile << "Results from: " << g.get_num_vertex() << "_" << g.get_num_edges() << std::endl;
    outfile << "Num inserts: " << kHeap.get_num_inserts() << std::endl;
    outfile << "Num updates: " << kHeap.get_num_updates() << std::endl;
    outfile << "Num deletes: " << kHeap.get_num_deletes() << std::endl;
    outfile << "Num sift_ups: " << kHeap.get_num_siftups() << std::endl;
    outfile << "Num sift_downs: " << kHeap.get_num_siftdowns() << std::endl;
    outfile << "------------------" << std::endl;
    return dist;
}

int main(int argc, char* argv[]){
    assert(argc == 3);
    unsigned vertex_num = 0, edges_num = 0;
    unsigned source_index = 0;
    unsigned target_index = 0;

    Graph g;
    Read::read_dimacs(std::cin, vertex_num, edges_num, g);
    srand48(time(0));

    //randomize pathing if value sent is "?"
    if(std::string (argv[1]) != "?"){
        source_index = std::stoi(argv[1]);
        target_index = std::stoi(argv[2]);
        source_index--;
        target_index--;
    }else{
        do{
            source_index = lrand48() % vertex_num;
            target_index = lrand48() % vertex_num;
        }while (source_index == target_index);
    }
    
    //call dijkstras algorithm and log the result
    try{
        std::vector<unsigned> distances = dijkstra(2,vertex_num,g,source_index);
        if(distances[target_index] != INT_MAX){
            std::cout << distances[target_index] << std::endl;
        }else{
            std::cout << "inf" << std::endl;
        }

    }catch(const std::exception& e){
        std::cerr << "Exceção capturada: " << e.what() << std::endl;
    }

    return 0;
}