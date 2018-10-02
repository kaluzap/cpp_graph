#include <iostream>
#include <vector>

using LIST = std::vector<std::vector<int> >;

#ifndef _GRAPH_
#define _GRAPH_

class GRAPH{
    
        LIST input_list;
        std::vector<int> outdegree;
    
    public:
        
        GRAPH();
        
        int get_number_of_nodes(void);
        
        int add_node(int n = 1);
        int add_link(int i, int j);     //j -> i
        
        int delete_node(int k);
        bool delete_link(int i, int j);
        
        bool is_link(int i, int j);
        
        int get_indegree(int i);
        int get_outdegree(int i);
        int get_degree(int i);
        
        class GRAPH transformation(void);
        
        
        void print_graph_dot(const char *file_name);
        void print_graph_list(void);
        
        
        int read_file(const char *file_name, int index);
        int write_file(const char *file_name, int index);
};

#endif