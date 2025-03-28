#include <vector>

class Graph {
public:
    struct Edge { 
        int weight;
        int target;
    };

private:
    int num_vertex;
    int num_edges;
    std::vector<std::vector<Edge>> graph_mem;

public:
    //constructors
    Graph(): num_vertex(0), num_edges(0){}
    
    //getters & setters
    int get_num_edges() { return num_edges; }
    int get_num_vertex() { return num_vertex; }
    std::vector<std::vector<Edge>> get_graph_mem() { return graph_mem; }
    std::vector<Edge> get_neighbors(int i) { return graph_mem[i]; }



    //functs
    void add_vertex(int i) {
        std::vector<Edge> vertex = {};
        this->graph_mem[i] = vertex;
    }

    void resize_mem(int n_mem) { 
        this->num_vertex = n_mem;
        graph_mem.resize(n_mem); 
    }

    void add_edge(int source, int target, int weight) {
        Edge new_edge = {weight, target};
        this->num_edges++;
        graph_mem[source].push_back(new_edge);
    }

    void print_graph(){
        std::vector<Graph::Edge> edges;
        for(int i = 0; i < graph_mem.size(); i++){
            edges = graph_mem[i];
            std::cout << "nodo: " << i << std::endl;
            for(int j = 0; j < edges.size(); j++)
                std::cout << "   target: " << edges[j].target << " peso:" << edges[j].weight << std::endl;
        }
    }
};
