/*
** Author:      Anthony Hicks
** Class:       CSCE 3110
** Instructor:  Dr. Eduardo Blanco
** Description: Converts a graph from a file to an Adjacency List
**              and runs BFS, DFS, and Topological Sort
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <utility>
#include <algorithm>
#include <sstream>

using std::istringstream;
using std::cout;
using std::cin;
using std::getline;
using std::string;
using std::ifstream;
using std::vector;
using std::list;
using std::queue;
using std::pair;

struct node{
    int id;
};

class Graph{
    private:
        vector< list<node> > g;
    public:
        void addEdge(int u, node v);
        bool populateGraph(char* inputfile);
        void printGraph();
        void bfs(int start);
        void dfs();
        void ts();
        Graph();
};

bool distCompare(const std::pair<int,unsigned int> &firstElement, const std::pair<int,unsigned int> &secondElement){
    
    return firstElement.second < secondElement.second;
}

bool idCompare(const std::pair<int,unsigned int> &firstElement, const std::pair<int,unsigned int> &secondElement){
    return (firstElement.first < secondElement.first && (firstElement.second == secondElement.second));
}

void Graph::dfs(){


}
void Graph::bfs(int start){
    queue<int> q;
    int size = g.size();

    vector< std::pair<int,unsigned int> > dist (size); //pair(vertex_label, distance)

    for(size_t i = 0; i < size; i++){
        dist[i] = std::make_pair (i, -1);
    }

    dist[start].second = 0; //because we're calculating the distance from start node
    q.push(start); //push 1 into the queue

    while (!q.empty()){
        int u = q.front();
        q.pop();
        for(list<node>::iterator i = g[u].begin(); i != g[u].end(); ++i){
            if(dist[(*i).id].second == -1){
                dist[(*i).id].second = dist[u].second + 1;
                q.push((*i).id);
            }
        }
    }

    std::sort(dist.begin() + 1, dist.end(), distCompare);
    std::stable_sort(dist.begin() + 1, dist.end(), idCompare);

    for(size_t i = 1; i < size; i++){
        cout << dist[i].first << " ";
        if(dist[i].second == -1){
            cout << "inf";
        }
        else{
            cout << dist[i].second << " ";
        }
        cout << '\n';
    }
}
Graph::Graph(){
    g.push_back(list<node>());
}

void Graph::addEdge(int u, node v){
    if((g.size()) - 1 < u){
        g.resize(u + 1);
    }
    g[u].push_back(v);
}

void Graph::printGraph(){
    for(size_t i = 1; i < g.size(); i++){
        for(list<node>::iterator j = g[i].begin(); j != g[i].end(); ++j){
            cout << (*j).id << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}
bool Graph::populateGraph(char* inputfile){

        string line;
        ifstream infile;
        //cout << "Opening file: \"" << inputfile << "\"\n";

        infile.open(inputfile); //open the file

        if(!infile.is_open()){
            cout << "Error opening file: \"" << inputfile << "\"\n";
            return false;
        }

        while(getline(infile, line)){

            istringstream ss(line);
            int first;
            ss >> first;

            node v;
            v.id = first;
            addEdge(first, v);

            string item;
            getline(ss, item, ' ');

            while(getline(ss, item, ' ')){
                node n;
                istringstream ns(item);
                ns >> n.id;
                addEdge(first, n);
            }
        }
        infile.close();

        return true;
}

int main(int argc, char* argv[]){

    //Wrong # of args
    if(argc != 3 && argc != 4){
        cout << "Incorrect number of arguments provided.\n";
        cout << "Format: ./graph bfs <vertex> inputfile\n";
        cout << "        ./graph bfs inputfile\n";
        cout << "        ./graph dfs inputfile\n";
        cout << "        ./graph ts inputfile\n";
        return 0;
    }
    else{
        Graph graph;
        char* inputFile;
        int bfs_start;

        if(argc == 3){
            inputFile = argv[2];
            bfs_start = 1;
        }
        else{
            inputFile = argv[3];
            bfs_start = argv[2][0] - 48;
        }

        if(!graph.populateGraph(inputFile)){
            cout << "Error populating graph.\n";
            return -1;
        }

        //graph.printGraph();

        string cmd;
        cmd = argv[1];

        if(cmd == "bfs"){
            graph.bfs(bfs_start);
        }
        else if(cmd == "dfs"){
            //graph.dfs();
        }
        else if(cmd == "ts"){
            //graph.ts();
        }
    }

    return 0;
}