/*
** Author:      Anthony Hicks
** Class:       CSCE 3110
** Instructor:  Dr. Eduardo Blanco
** Description: Converts a graph from a file to an Adjacency List
**              and runs BFS, DFS, and Topological Sort
*/

#include "graph.cpp"

int main(int argc, char* argv[]){
    
    if(argc != 3 && argc != 4){                                        //Wrong number of arguments, print the valid format
        cout << "Incorrect number of arguments provided.\n";
        cout << "Format: ./a.out bfs <vertex> inputfile\n";
        cout << "        ./a.out bfs inputfile\n";                     //BFS will default to vertex with ID=1
        cout << "        ./a.out dfs inputfile\n";
        cout << "        ./a.out ts inputfile\n";
        return 0;
    }
    else{
        Graph graph;                                                   //Construct our graph object
        char* inputFile;
        int bfs_start;
                                                                       //Determine which argument is the input file and the starting vertex for BFS
        if(argc == 3){
            inputFile = argv[2];
            bfs_start = 1;
        }
        else{
            inputFile = argv[3];
            bfs_start = argv[2][0] - 48;
        }

        if(!graph.populateGraph(inputFile)){                           //Populate the graph and return an error if there was an issue
            cout << "Error populating graph.\n";
            return -1;
        }

        string cmd;                                                    //Determine which algorithm to run
        cmd = argv[1];

        if(cmd == "bfs"){                                              //Run BFS and print
            graph.print_bfs(graph.bfs(bfs_start));
        }
        else if(cmd == "dfs"){                                         //Run DFS and print
            graph.print_dfs(graph.dfs());
        }
        else if(cmd == "ts"){                                          //Run TS and print
            graph.ts();
        }
        else if(cmd == "isConnected"){
            if(graph.isConnected(graph.bfs(bfs_start))){
                cout << "yes\n";
            }
            else cout << "no\n";
        }
    }

    return 0;
}
