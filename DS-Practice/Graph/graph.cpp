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

#include "graph.h"

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

/* Heuristic for sorting results of BFS by increasing distance */
bool distCompare(const std::pair<int,unsigned int> &firstElement, const std::pair<int,unsigned int> &secondElement){
    return firstElement.second < secondElement.second;
}

/* Heuristic for sorting results of BFS also by vertex ID */
bool idCompare(const std::pair<int,unsigned int> &firstElement, const std::pair<int,unsigned int> &secondElement){
    return (firstElement.first < secondElement.first && (firstElement.second == secondElement.second));
}

/* Heuristic for sorting results of DFS by increasing discovery time */
bool discoveryCompare(const node &firstElem, const node &secondElem){
    return firstElem.d < secondElem.d;
}

/* Heuristic for sorting results of DFS by decreasing finish time, aka TS */
bool tsCompare(const node &firstElem, const node &secondElem){
    return firstElem.f > secondElem.f;
}

/* node class constructor */
node::node(){
    state = undiscovered; //initialize all nodes' state to undiscovered and finish time to 0
    f = 0;
}

/**************************************************************** 
* Function     : Graph::addEdge                                 *
* Parameter(s) : ID of first vertex, node object of second      *
* Return-Value : N/A                                            *
* Description  : Inserts an "edge" into the adjacency list      *
*****************************************************************/
void Graph::addEdge(int u, node v){
    if((g.size()) - 1 < u){           //I don't know why the vector isn't handling this itself.
        g.resize(u + 1);
    }
    g[u].push_back(v);
}


/**************************************************************** 
* Function     : Graph::populateGraph                           *
* Parameter(s) : char* for input file to open                   *
* Return-Value : boolean for success/failure                    *
* Description  : Populates the adjacency list from a file       *
*****************************************************************/
bool Graph::populateGraph(char* inputfile){

        string line;                                                   //String to process each line of the file
        ifstream infile;                                               //Input stream

        infile.open(inputfile);                                        //Open the file

        if(!infile.is_open()){                                         //If we have a problem opening the file, abort.
            cout << "Error opening file: \"" << inputfile << "\"\n";
            return false;
        }

        while(getline(infile, line)){                                  //Read the input line-by-line

            istringstream ss(line);                                    //Stringstream to easily convert data into respective types
            int first;                                                 //First number on each line is the ID of the vertex
            ss >> first;

            node v;                                                    //Insert the vertex
            v.id = first;                                              //This does create an Adjacency List where the initial vertex is actually existing twice in the list.
            addEdge(first, v);                                         //1 -> 1 -> 2 -> 3 -> 4
                                                                       //2 -> 2 -> 3 
            string item;                                               //3 -> 3 -> 1 -> 2
            getline(ss, item, ' ');                                    //4 -> 4 -> 1

            while(getline(ss, item, ' ')){                             //Read each line item-by-item
                node n;                                                //Create a node for each item, and insert into the AdjList
                istringstream ns(item);
                ns >> n.id;
                addEdge(first, n);
            }
        }
        infile.close();                                                //Close the file

        return true;                                                   //Successfully populated the graph
}


/**************************************************************** 
* Function     : Graph::printGraph                              *
* Parameter(s) : N/A                                            *
* Return-Value : N/A                                            *
* Description  : Prints the adjacency list                      *
*****************************************************************/
void Graph::printGraph(){
    for(size_t i = 1; i < g.size(); i++){
        for(vector<node>::iterator j = g[i].begin(); j != g[i].end(); ++j){
            cout << (*j).id << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}


/**************************************************************** 
* Function     : Graph::bfs                                     *
* Parameter(s) : ID of vertex that we will pulsating from       *
* Return-Value : vector of pairs to denote distance             *
* Description  : Breadth-First Search                           *
*****************************************************************/
vector< pair<int,unsigned int> > Graph::bfs(int start){
    queue<int> q;
    size_t size = g.size();

    vector< std::pair<int,unsigned int> > dist (size); //pair(vertex_id, distance)

    for(size_t i = 0; i < size; i++){                  //Initialize the distance of all nodes to "infinity"
        dist[i] = std::make_pair (i, -1);              //I suppose this does limit me to distances that are < UNSIGNED_INT_MAX
    }

    dist[start].second = 0;                            //Set distance of the starting vertex to 0
    q.push(start);                                     //Push starting vertex's id into the queue

    while (!q.empty()){                                //While the queue isn't empty
        int u = q.front();                             //Pop the next element off
        q.pop();
                                                       //for all nodes connected to u, if we haven't set the distance of that node yet, set distance to distance of u + 1, and push that node into the queue
        for(vector<node>::iterator i = g[u].begin(); i != g[u].end(); ++i){
            if(dist[(*i).id].second == -1){
                dist[(*i).id].second = dist[u].second + 1;
                q.push((*i).id);
            }
        }
    }

    return dist;
}


/**************************************************************** 
* Function     : Graph::print_bfs                               *
* Parameter(s) : vector of pairs                                *
* Return-Value : N/A                                            *
* Description  : Customizable print function for BFS            *
*****************************************************************/
void Graph::print_bfs(vector< pair<int,unsigned int> > after_bfs){
    std::sort(after_bfs.begin() + 1, after_bfs.end(), distCompare);       //Sort by distance, then by ID while retaining the original sort
    std::stable_sort(after_bfs.begin() + 1, after_bfs.end(), idCompare);

    size_t size = after_bfs.size();

    for(size_t i = 1; i < size; i++){
        cout << after_bfs[i].first << " ";
        if(after_bfs[i].second == -1){
            cout << "inf";
        }
        else{
            cout << after_bfs[i].second << " ";
        }
        cout << '\n';
    }
}


/**************************************************************** 
* Function     : Graph::dfs                                     *
* Parameter(s) : N/A                                            *
* Return-Value : vector of nodes with updated finish times, etc *
* Description  : Depth-First Search                             *
*****************************************************************/
vector<node> Graph::dfs(){
    unsigned int t = 0;                         //time = 0
    size_t size = g.size();

    vector<node> states (size);                 //Create vector of nodes to easily reference values of state/discoveryTime/finishTime
                                                //and more importantly, to not work with the nodes in the adjacency list, since those nodes are often repeated

    for(size_t i = 0; i < size; i++){           //Initialize all of the vertices' states to undiscovered
        states[i].state = undiscovered;
        states[i].id = i;                       
    }

    for(size_t i = 1; i < size; i++){           //For all vertices, if they are undiscovered, visit them.
        if(states[i].state == undiscovered){
            dfs_visit(states, i, t);
        }
    }

    return states;                              //Return for customized print function
}


/**************************************************************** 
* Function     : Graph::dfs_visit                               *
* Parameter(s) : ref->(vector of nodes), id of node, ref->time  *
* Return-Value : N/A                                            *
* Description  : Marks vertices as discovered/finished          *
*****************************************************************/
void Graph::dfs_visit(vector<node>& st, int label, unsigned int& t){
    t++;                                                                //Increment time
    st[label].d = t;                                                    //Set discovery time
    st[label].state = discovered;                                       //Mark as discovered
    
    for(size_t i = 1; i < g[label].size(); ++i){                        //For all nodes adjacent to the current one
        if(st[g[label][i].id].state == undiscovered){                   //check if they are undiscovered
            dfs_visit(st, g[label][i].id, t);                           //visit them
        }
    }

    t++;                                                                //Increment time
    st[label].f = t;                                                    //Set finish time
    st[label].state = finished;                                         //Mark as finished
}


/**************************************************************** 
* Function     : Graph::print_dfs                               *
* Parameter(s) : vector of nodes                                *
* Return-Value : N/A                                            *
* Description  : Customizable printing function for dfs         *
*****************************************************************/
void Graph::print_dfs(vector<node> after_dfs){  //Sort by discovery time
    sort(after_dfs.begin() + 1, after_dfs.end(), discoveryCompare);

    for(size_t i = 1; i < after_dfs.size(); i++){
        cout << after_dfs[i].id << " " << after_dfs[i].d << " " << after_dfs[i].f << "\n";
    }
}


/**************************************************************** 
* Function     : Graph::ts                                      *
* Parameter(s) : N/A                                            *
* Return-Value : N/A                                            *
* Description  : Topological Sort executed by running DFS, then *
*                sorting the output by decreasing finish time.  *
*****************************************************************/
void Graph::ts(){
    vector<node> after_dfs = dfs();

    sort(after_dfs.begin() + 1, after_dfs.end(), tsCompare);

    for(size_t i = 1; i < after_dfs.size(); i++){
        cout << after_dfs[i].id << '\n';
    }
}


/**************************************************************** 
* Function     : Graph::isConnected                             *
* Parameter(s) : vector of pairs as a result of bfs             *
* Return-Value : true if the graph is connected, else false     *
* Description  : Checks whether the graph is connected          *
*****************************************************************/
bool Graph::isConnected(vector< pair<int,unsigned int> > after_bfs){
    size_t size = after_bfs.size();

    for(size_t i = 1; i < size; i++){
        if(after_bfs[i].second == -1){
            return false;
        }
    }

    return true;
}

/*
** Constructor for Graph Class
** Unfortunately, I do not know why I must have this line in order for my code to work.
** I need to read up on class member variables and their initialization.
*/
Graph::Graph(){
    g.push_back(vector<node>());
}