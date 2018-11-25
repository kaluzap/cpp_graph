#include <iostream>
#include <vector>
#include <string>


#ifndef _MY_GRAPH_
#define _MY_GRAPH_


namespace my_graph{
    
    using LIST = std::vector<std::vector<int>>;

    class GRAPH{
    
        LIST input_list;
        std::vector<int> outdegree;
    
    public:
        
        GRAPH();    //graph with zero nodes and zero links
        GRAPH(int n); //graph with N nodes and no connections
        GRAPH(class GRAPH &A);  //copy constructor
        GRAPH &operator=(const GRAPH &in);     //overloading operator =
        
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
        
        void print_graph_dot(const std::string file_name);
        void print_graph_list(void);
        
        int read_file(const std::string file_name, int index);
        int write_file(const std::string file_name, int index);
    };

}

#endif
