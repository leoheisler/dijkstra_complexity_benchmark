#include <istream>
#include <iostream>
#include <sstream>
#include <string>
#include "_Graph.h"

class Read
{
public:

  static void read_dimacs(std::istream& in, unsigned& vertex_num, unsigned& edges_num, Graph& g) {
    std::string line="", dummy;
    while (line.substr(0,4) != "p sp")
      getline(in,line);
  
    // (1) get nodes and edges
    std::stringstream linestr;
    linestr.str(line);
    linestr >> dummy >> dummy >> vertex_num >> edges_num;
    g.resize_mem(vertex_num);
    unsigned i=0;
    while (i++ < edges_num) {
      getline(in,line);
      if (line.substr(0,2) == "a ") {
        std::stringstream arc(line);
        unsigned u,v,w;
        char ac;
        arc >> ac >> u >> v >> w;
        // processa arco (u,v) com peso w
        g.add_edge(u,v,w);
      }
    }
  }

};



