#include "_Read.h"
#include <cassert>

int main(int argc, char* argv[]){
    assert(argc == 3);
    unsigned vertex_num = 0, edges_num = 0;
    unsigned source_index = std::stoi(argv[1]);
    unsigned target_index = std::stoi(argv[2]);
    Graph g;
    Read::read_dimacs(std::cin, vertex_num, edges_num, g);
    std::cout << "source: " << source_index << " target: " << target_index << std::endl;
    std::cout << "Grafo lido com " << vertex_num << " vértices e " << edges_num << " arestas.\n";
    std::cout << "Grafo lido com " << g.get_graph_mem().size() << " vértices e " << g.get_num_edges() << " arestas.\n";

    return 0;
}