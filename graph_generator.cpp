/**
 * \file gen.cpp
 *   \author Marcus Ritt <mrpritt@inf.ufrgs.br>
 *   \date Time-stamp: <2024-07-23 13:03:31 ritt>
 */

#include <cassert>
#include <iostream>
#include <fstream>
#include "_Graph.h"
using namespace std;
const unsigned maxweight = 1000;


int main(int argc, char *argv[]) {
    assert(argc == 3);
    unsigned vertex_number = atoi(argv[1]);
    double probability = atof(argv[2]);

    srand48(time(0));

    // (1) generate random graph
    Graph g;
    g.resize_mem(vertex_number);
    
    for (unsigned i = 0; i < vertex_number; i++)
        for (unsigned j = 0; j < vertex_number; j++)
            if (i != j && drand48() < probability) {
                int weight = lrand48() % maxweight;
                g.add_edge(i + 1, j + 1, weight);
            }
    
    
    // (2) print out in DIMACS challenge format
    ofstream outfile("graphs/4_vertices_foll.gr");
    if (!outfile.is_open()) {
        cerr << "Erro ao abrir o arquivo para escrita." << endl;
        return 1;
    }
    outfile << "p sp " << g.get_num_vertex() << " " << g.get_num_edges() << endl;

    for (int i = 0; i < g.get_num_vertex(); i++){
        std::vector<Graph::Edge> edges = g.get_graph_mem().at(i);
        for(int j = 0; j  < edges.size(); j++){
            Graph::Edge edge = edges.at(j);
            outfile << "a " << i + 1 << " " << edge.target + 1 << " " << edge.weight << endl;
        }

    }
}