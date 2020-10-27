#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
using namespace std;

static int isUndirectedMatrix(vector<vector<double>> matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.size(); j++){
            if(matrix[i][j] != matrix[j][i]){
                return 0;
            }
        }
    }
    return 1;
}

static vector<vector<double>> randomMatrixGraph(int graphSize, double edgeDensity, double minDistance, double maxDistance){
    srand(time(nullptr));
    vector<vector<double>> matrix(graphSize, vector<double>(graphSize, -1)); // Construct a matrix with graphSize for a graph with no edges (-1)
    for(int i = 0; i < graphSize; i++){
        for(int j = 0; j < graphSize; j++){
            if(i == j) continue; // No loops
            if(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) >= edgeDensity) continue; // This edge is not going to exist
            matrix[i][j] = matrix[j][i] = minDistance + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX/(maxDistance-minDistance)));
        }
    }
    return matrix;
}

// The representation selected is a matrix which values indicates the weight of the edge. A negative value indicates there is no edge.
class Graph{
    private:
    vector<vector<double>> matrix;

    public:
    Graph(){ // Default constructor
        matrix = vector<vector<double>>();
    }

    Graph(vector<vector<double>> matrix){
        if(isUndirectedMatrix(matrix)){
            this->matrix = matrix;
        }
        else{
            cout << "Error: graph is not undirected" << endl;
        }
    }

    int V(){ // Returns the number of vertices in the graph
        return matrix.size();
    }

    int E(){ // Returns the number of edges in the graph
        int res = 0;
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix.size(); j++){
                res += adjacent(i, j);
            }
        }
        return res;
    }

    int adjacent(int x, int y){ // Tests whether there is an edge from node x to node y
        if(matrix[x][y] >= 0){
            return 1;
        }
        return 0;
    }

    vector<int> neighbors(int x){ // Lists all nodes y such that there is an edge from x to y
        vector<int> res;
        for(int i = 0; i < matrix.size(); i++){
            if(adjacent(x, i)){
                res.push_back(i);
            }
        }
        return res;
    }

    int add(int x, int y, int weight){ // Adds to the graph the edge from x to y, if it is not there
        if(!adjacent(x, y)){
            matrix[x][y] = weight;
            return 1;
        }
        return 0;
    }

    int del(int x, int y){ // Removes the edge from x to y, if it is there
        if(adjacent(x, y)){
            matrix[x][y] = -1;
            return 1;
        }
        return 0;
    }

    int get_node_value(int x){ // Returns the value associated with the node x
        // TODO
    }

    void set_node_value(int x, int a){ // Sets the value associated with the node x to a
        // TODO
    }

    double get_edge_value(int x, int y){ // Returns the value associated to the edge (x, y)
        return matrix[x][y];
    }

    void set_edge_value(int x, int y, int v){ // Sets the value associated to the edge (x, y) to v
        matrix[x][y] = v;
    }
}; // End Graph class

class PriorityQueue{
    public:
    class QueueElement{
        private:
        int id;
        double priority;
        QueueElement * next;

        public:
        QueueElement(int id = 0, double priority = 0.0, QueueElement * next = nullptr):id(id), priority(priority), next(next){}
    }; // End of class queueElement

    // Constructors
    PriorityQueue():head(nullptr), cursor(nullptr){} // Default constructor
    
    // int getId(){ return cursor->id;}
    // double getPriority(){ return cursos->priority;}
    void advance(){cursor = cursor->next;}
    
    void print(){
        QueueElement * head = this->head;
        while(head != nullptr){
            cout << /*head->id << ":" << */head->priority << "  ->  ";
            head = head->next;
        }
        cout << "###" << endl;
    }

    void insert(int id, double priority){ // Insert queue_element into queue
        if(head == nullptr || head->priority > priority){
            cursor = head = new QueueElement(id, priority, head);
        }
        else{
            QueueElement * head = this->head;
            while(head->next != nullptr && head->next->priority <= priority){
                head = head->next;
            }
            head->next = new QueueElement(id, priority, head->next);
        }
    }

    // ~PriorityQueue(){   // Destructor
    //     PriorityQueue * temp;
    //     while(){
    //     }
    // }

    // Updates the priority of a particular element and returns 1. If an element with the given id does not exists, nothing occurs and returns 0.
    int chgPriority(int id, double priority){ // Changes the priority (node value) of queue element
        if(head == nullptr) return 0;
        if(head->id == id){
            head->priority = priority;
            return 1;
        }
        QueueElement * head = this->head;
        while(head->next != nullptr && head->next->id != id){
            head = head->next;
        }
        if(head->next != nullptr){
            head->next->priority = priority;
            return 1;
        }
        return 0;
    }

    int minPriority(){ // Removes and return the top element of the queue
        int res = -1;
        if(head != nullptr){
            res = head->id;
            QueueElement * temp = head;
            head = head->next;
            delete temp;
        }
        return res;
    }

    int contains(int id){ // Does the queue contain queue_element
        if(head == nullptr) return 0;
        if(head->id == id) return 1;
        QueueElement * head = this->head;
        while(head->next != nullptr){
            head = head->next;
            if(head->id == id) return 1;
        }
        return 0;
    }


    int top(){ // Returns the top element of the queue
        return id;
    }

    int size(){ // Returns the number of queue_elements
        int size = 0;
        PriorityQueue * queue = this;
        while(queue->next != nullptr){
            size++;
            queue = queue->next;
        }
        return size;
    }

    private:
    QueueElement * head;
    QueueElement * cursor;
}; // End PriorityQueue class

class ShortestPath{
    private:
    Graph graph;
    vector<int> dist;
    vector<int> prev;

    public:
    ShortestPath(){ // Default constructor
        graph = new Graph();
    }

    ShortestPath(Graph graph){
        this->graph = graph;
    }

    vertices(list<int> list){ // List of vertices in G(V, E)

    }

    list<int> path(int u, int w){ // Find shortest path between u-w and returns the sequence of vertices representing shortest path u-v1-v2-...-vn-w
        dist[u] = 0;    // Initialization
        PriorityQueue Q = new PriorityQueue();
        for(int v = 0; v < graph.V(); v++){
            if(i != u){
                dist[v] = INFINITY; // Unknown distance from source to v
                prev[v] = UNDEFINED;    // Predecesor of v
            }
            Q.insert(v, dist[v]);
        }

        while(Q.size() != 0){   // The main loop
            u = Q.top();    // Return best vertex
            Q.minPriority();    // Remove best vertex
            vector<int> neighbors = graph.neighbors(u); // Only v that are still in Q
            for(int v = 0; v < neighbors.size(); v++){
                int alt = dist[u] + graph.get_edge_value(u, v);
                if(alt < dist[v]){
                    dist[v] = alt;
                    prev[v] = u;
                    Q.chgPriority(v, alt);
                }
            }
        }
        return dist, prev;
    }

    int path_size(int u, int w){ // Returns the path cost associated with the shortest path

    }
}; // End ShortestPath class

int main(){
    Graph graph = Graph(randomMatrixGraph(50, 0.2, 1.0, 10.0));
    Graph graph = Graph(randomMatrixGraph(50, 0.4, 1.0, 10.0));
    for(int i = 0; i < graph.V(); i++){
        for(int j = 0; j < graph.V(); j++){
            cout << graph.get_edge_value(i, j) << endl;
        }
    }

    return 0;
}