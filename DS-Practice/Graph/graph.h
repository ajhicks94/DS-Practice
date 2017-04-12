/*
** Author:      Anthony Hicks
** Class:       CSCE 3110
** Instructor:  
** Description: Converts a graph from a file to an Adjacency List
**              and runs BFS, DFS, and Topological Sort
*/
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

/* DFS States */
enum State{
    undiscovered, discovered, finished
};

class node{
    public:
        int id;
        State state;      //dfs: undiscovered (1), discovered (2), or finished (3)
        unsigned int d;   //time of discovery
        unsigned int f;   //time of finishing
        node();           //Constructor
};

class Graph{
    private:              //initially was a vector of lists, but changed it to vector of vectors out of paranoia so 
                          //*technically* it is still an Adjacency List since the size is not defined initially
        std::vector< std::vector<node> > g;
    public:
        void addEdge(int u, node v);
        bool populateGraph(char* inputfile);
        void printGraph();
        std::vector< std::pair<int,unsigned int> > bfs(int start);
        void print_bfs(std::vector< std::pair<int,unsigned int> > after_bfs);
        std::vector<node> dfs();
        void dfs_visit(std::vector<node>& st, int label, unsigned int& t);
        void print_dfs(std::vector<node> after_dfs);
        void ts();
        Graph();
};

/* Heuristic for sorting results of BFS by increasing distance */
bool distCompare(const std::pair<int,unsigned int> &firstElement, const std::pair<int,unsigned int> &secondElement);

/* Heuristic for sorting results of BFS also by vertex ID */
bool idCompare(const std::pair<int,unsigned int> &firstElement, const std::pair<int,unsigned int> &secondElement);

/* Heuristic for sorting results of DFS by increasing discovery time */
bool discoveryCompare(const node &firstElem, const node &secondElem);

/* Heuristic for sorting results of DFS by decreasing finish time, aka TS */
bool tsCompare(const node &firstElem, const node &secondElem);

#endif //GRAPH_H