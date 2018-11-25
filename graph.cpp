#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

#include "graph.hxx"

//using namespace std;

my_graph::GRAPH::GRAPH()
{
    return;
}


my_graph::GRAPH::GRAPH(int n)
{
    add_node(n);
    return;
}


my_graph::GRAPH::GRAPH(class my_graph::GRAPH &in)
{
    input_list = in.input_list;
    outdegree = in.outdegree;
    return;
}


my_graph::GRAPH &my_graph::GRAPH::operator=(const my_graph::GRAPH &in)
{
    if(this != &in) { // self-assignment check expected
        input_list = in.input_list;
        outdegree = in.outdegree;
    }
    
    return *this;
}


int my_graph::GRAPH::get_number_of_nodes(void)
{
    return input_list.size();
}


int my_graph::GRAPH::add_node(int n)
{
    for(int i=0; i<n; i++){
        input_list.push_back({});
        outdegree.push_back(0);
    }
    return input_list.size()-1;
}


int my_graph::GRAPH::add_link(int i, int j)
{
    if( (i >= input_list.size()) || (i < 0) ) return -1;
    if( (j >= input_list.size()) || (j < 0) ) return -2;
    if( i == j ) return -3;
    
    input_list[i].push_back(j);
    outdegree[j]++;
    
    return j;
}


bool my_graph::GRAPH::is_link(int i, int j)
{
    auto k = std::find(input_list[i].begin(), input_list[i].end(), j);
    
    if ( k != input_list[i].end() ) return true;
    
    return false;
}


bool my_graph::GRAPH::delete_link(int i, int j)
{
    auto k = std::find(begin(input_list[i]), end(input_list[i]), j);
    
    if ( k != input_list[i].end() ){
        input_list[i].erase(k);
        outdegree[j]--;
        return true;
    }

    return false;
}


int my_graph::GRAPH::delete_node(int i)
{
    
    if( (i >= input_list.size()) || (i < 0) ) return -1;
    
    //deleting connections from i to the other nodes
    for(int k=0; k < input_list.size(); k++) delete_link(k,i);
    
    //deleting node i
    input_list.erase(begin(input_list) + i);
    outdegree.erase(begin(outdegree) + i);
    
    //renaming the nodes with index larger than i
    for(int m=0; m < input_list.size(); m++){
        for(int n=0; n < input_list[m].size(); n++){
            if(input_list[m][n] > i) input_list[m][n] -= 1; 
        }
    }
    
    return i;
}


int my_graph::GRAPH::get_indegree(int i)
{
    return input_list[i].size();
}


int my_graph::GRAPH::get_outdegree(int i)
{
    return outdegree[i];
}


int my_graph::GRAPH::get_degree(int i)
{
    return input_list[i].size() + outdegree[i];
}


void my_graph::GRAPH::print_graph_dot(const std::string file_name)
{
    std::ofstream myfile;
    myfile.open(file_name);
    
    myfile << "digraph migraph{" << std::endl;
    
    myfile << "node [shape=circle,fixedsize=true]; ";
    
    for(int i=0; i < input_list.size(); i++) myfile << i << " ";
    myfile << ";" << std::endl;
    
    
    for(int i=0; i < input_list.size(); i++){
        for(int j=0; j < input_list[i].size(); j++){
        
            myfile << "\t" << input_list[i][j] << " -> " << i << ";" << std::endl;
        }
    }
    
    myfile << "}" << std::endl;
    myfile.close();
    
    return;
}


void my_graph::GRAPH::print_graph_list(void)
{
 
    for(int i=0; i < input_list.size(); i++){
        for(int j=0; j < input_list[i].size(); j++){
        
            std::cout << input_list[i][j] << " -> " << i <<  std::endl;
        }
    }
  
    return;
}



class my_graph::GRAPH my_graph::GRAPH::transformation(void)
{
    
    class GRAPH temp;
    
    int number_of_links(0);
    
    for(int i=0; i < input_list.size(); i++) number_of_links += input_list[i].size();
    
    temp.add_node(number_of_links);
    
    /*
    int input_link = 0;
    for(int i=0; i < input_list.size(); i++){
        for(int j=0; j < input_list.size(); j++){
            
            if(!is_link(j,i)) continue;
            
            int output_link = 0;
            for(int k=0; k < input_list.size(); k++){
                for(int l=0; l < input_list.size(); l++){
                    
                    if(!is_link(l,k)) continue;
                    
                    if( j == k) temp.add_link(output_link, input_link);
                    
                    output_link++;
                }
            }
        
            input_link++;
        }
    }
    */
    
    
    int input_link = 0;
    for(int i=0; i < input_list.size(); i++){
        for(int j=0; j < input_list[i].size(); j++){
  
            //[j] -> i      (input link)

            int output_link = 0;
            for(int k=0; k < input_list.size(); k++){
                for(int l=0; l < input_list[k].size(); l++){
                    
                    //[l] -> k   (output link)
                    
                    if( i == input_list[k][l]) temp.add_link(output_link, input_link);
                                        
                    output_link++;
                }
            }
        
            input_link++;
        }
    }
    
    
    return temp;
}



int my_graph::GRAPH::read_file(const std::string file_name, int index)
{
    std::ifstream myfile;
    myfile.open(file_name);
    
    if (!myfile.is_open()){
        std::cout << "Error with file: " << file_name << std::endl;
        return -1;
    }
    
    input_list.clear();
    
    int N;
    std::string temp;
    
    std::string line;
    while ( getline (myfile,line) ){
        //cout << line << '\n';
      
        std::istringstream word(line);
        word >> temp >> N;
        
        if( (temp == "GRAPH") && (N == index) ){
        
            getline(myfile,line);
            std::istringstream word(line);
            word >> temp >> N;
        
            add_node(N);
            
            
            while(getline(myfile, line)){
                
                int i,j;
                
                std::istringstream word(line);
                
                temp = "_";
                word >> i >> temp >> j;
        
                if(temp != "->") break;
                  
                add_link(j,i);
                
                //cout << line << endl;
            }
            
            
            
            return index;    
        }
        
        
    }
    
    return -1;
}

int my_graph::GRAPH::write_file(const std::string file_name, int index)
{
    std::ofstream myfile;
    myfile.open(file_name, std::ofstream::app );
    
    
    if (!myfile.is_open()){
        std::cout << "Error with file: " << file_name << std::endl;
        return -1;
    }
    
    myfile << "GRAPH " << index << std::endl;
    myfile << "N " << input_list.size() << std::endl;
    
    for(int i=0; i < input_list.size(); i++){
        for(int j=0; j < input_list[i].size(); j++){
        
            myfile << input_list[i][j] << " -> " << i << std::endl;
        }
    }
    
    myfile << std::endl;
    myfile.close();
    
    return index;
    
}
