#include "_Read.h"
#include "_Heap.h"
#include <cassert>
#include <climits>
#include <fstream>
#include <chrono>


std::vector<unsigned> dijkstra(int k, int num_vertices, Graph& g, Heap& kHeap, unsigned source_index){

    //start funct
    std::vector<unsigned> dist(num_vertices, INT_MAX); 
    dist[source_index] = 0;

    //insert source node
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
    return dist;
}

//calculates avarage for r_numbers
double calc_avg(std::vector<double>  r_values){
    double avg = 0;
    for(double val : r_values){
        avg += val;
    }

    avg =  avg / r_values.size();
    return avg;
}

// ARGS
// source_index, source vertex index
// target_index, target vertex index
// k, k-ary heap children
// file_name, graph file configuration name
// outfile_path, where the statistics will be printed
int main(int argc, char* argv[]){
    assert(argc <= 6 && argc >= 3);
    unsigned vertex_num = 0, edges_num = 0;
    unsigned source_index = 0;
    unsigned target_index = 0;
    int k = std::stoi(argv[3]);
    std::string file_name = argv[4];
    std::string outfile_path = argv[5];

    Heap kHeap(k);
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
        //calculate time
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<unsigned> distances = dijkstra(k,vertex_num,g,kHeap,source_index);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = finish - start;
        
        //set result file to print statistics
        std::ofstream outfile(outfile_path,std::ios::app);
        if (!outfile.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
            exit;
        }

        //print csv
        std::vector<double>  r_values = kHeap.get_r_values();
        double avg = calc_avg(r_values);
        outfile << file_name << "," << k << ",";
        outfile << g.get_num_vertex() << "," << g.get_num_edges() << ",";
        outfile << kHeap.get_num_inserts() << ",";
        outfile << kHeap.get_num_updates() << ",";
        outfile << kHeap.get_num_deletes() << ",";
        outfile << avg << ",";
        outfile << duration.count() << std::endl;

        //log result
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