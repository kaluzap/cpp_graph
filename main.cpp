#include <iostream>
#include <vector>

#include "graph.hxx"


int main(int argc, char **argv)
{
    
    std::vector<std::string> arguments(argv, argv + argc);
    
    
    std::cout << arguments[0] << std::endl;
    std::cout << arguments[1] << std::endl;
    
    
    my_graph::GRAPH A, B, C, D;

    //B.read_file(argv[1], 4);
    
    //cout << "Size: " << B.get_number_of_nodes() << endl;
    //B.print_graph_list();
    
    //return 0;
    
    A.add_node(4);
    A.add_node();
    
    A.add_link(1,0);
    A.add_link(3,0);
    A.add_link(2,1);
    A.add_link(4,2);
    A.add_link(0,3);
    A.add_link(1,4);
    A.add_link(2,4);
    
    A.print_graph_dot("uno.dot");
    A.print_graph_list();
    A.write_file(arguments[1], 1);
    
    B = A.transformation();
    
    std::cout << "\n";
    
    B.print_graph_dot("dos.dot");
    B.print_graph_list();
    B.write_file(arguments[1], 2);
    
    C = B.transformation();
    
    std::cout << "\n";
    
    C.print_graph_dot("tres.dot");
    C.print_graph_list();
    C.write_file(arguments[1], 3);
    
    D = C.transformation();
    
    std::cout << "\n";
    
    D.print_graph_dot("cuatro.dot");
    D.print_graph_list();
    D.write_file(arguments[1], 4);
    A = D;
    
    return 0;
}
