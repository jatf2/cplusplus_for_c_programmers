#include <iostream>
#include <vector>
#include <list>
#include <limits>
using namespace std;

static int isUndirectedMatrix(const vector<vector<double>> matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.size(); j++){
            if(matrix[i][j] != matrix[j][i]){
                return 0;
            }
        }
    }
    return 1;
}

static vector<vector<double>> randomMatrixGraph(const int graphSize, const double edgeDensity, const double minDistance, const double maxDistance){
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

    int adjacent(const int x, const int y){ // Tests whether there is an edge from node x to node y
        if(matrix[x][y] >= 0){
            return 1;
        }
        return 0;
    }

    vector<int> neighbors(const int x){ // Lists all nodes y such that there is an edge from x to y
        vector<int> res;
        for(int i = 0; i < matrix.size(); i++){
            if(adjacent(x, i)){
                res.push_back(i);
            }
        }
        return res;
    }

    int add(const int x, const int y, const int weight){ // Adds to the graph the edge from x to y, if it is not there
        if(!adjacent(x, y)){
            matrix[x][y] = weight;
            return 1;
        }
        return 0;
    }

    int del(const int x, const int y){ // Removes the edge from x to y, if it is there
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

    double get_edge_value(const int x, const int y){ // Returns the value associated to the edge (x, y)
        if(matrix[x][y] < 0){ cout << "Aborting..." << endl; abort();}
        return matrix[x][y];
    }

    void set_edge_value(const int x, const int y, const int v){ // Sets the value associated to the edge (x, y) to v
        matrix[x][y] = v;
    }
}; // End Graph class

class PriorityQueue{
    public:
    class QueueElement{
        public:
        int id;
        double priority;
        QueueElement * next;

        QueueElement(int id = 0, double priority = 0.0, QueueElement * next = nullptr):id(id), priority(priority), next(next){}
    }; // End of class queueElement

    // Constructors
    PriorityQueue():head(nullptr), cursor(nullptr){} // Default constructor
    
    void advance(){cursor = cursor->next;}
    
    void print(){
        QueueElement * temp = head;
        while(head != nullptr){
            cout << /*temp->id << ":" << */temp->priority << "  ->  ";
            temp = temp->next;
        }
        cout << "###" << endl;
    }

    void insert(const int id, const double priority){ // Insert queue_element into queue
        // If head element has a worst priority
        if(head == nullptr || (head->priority > priority && priority >= 0)){
            // Link the new element with the head and update the head
            cursor = head = new QueueElement(id, priority, head);
        }
        else{
            QueueElement * temp = head;
            // Search for the element that will precede the new element
            while(temp->next != nullptr && (temp->next->priority <= priority || priority < 0)){
                temp = temp->next;
            }

            // Link the element with the new element and link the new element with next element
            temp->next = new QueueElement(id, priority, temp->next);
        }
    }

    // ~PriorityQueue(){   // Destructor
    //     PriorityQueue * temp;
    //     while(){
    //     }
    // }

    // Returns -1 if element does not exists, 0 if the deletes succesfully
    int erase(const int id){
        QueueElement* temp = head;
        QueueElement* prev = nullptr;

        // If head element itself holds the id to be deleted
        if(head != nullptr && head->id == id){
            head = head->next; // Change head
            delete temp;    // Deallocate
            return 0;
        }

        // Else search for the id to be deleted and keep track of the previous element
        while(temp != nullptr && temp->id != id){
            prev = temp;
            temp = temp->next;
        }

        // If element was not present
        if(temp == nullptr) return -1;

        // Unlink the element
        prev->next = temp->next;

        // Bring the memory to the heap
        delete temp;

        return 0;
    }

    // Updates the priority of a particular element. Return 0 if successful, -1 if element does not exists.
    int chgPriority(const int id, const double priority){ // Changes the priority (node value) of queue element
        erase(id);
        insert(id, priority);
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

    int contains(const int id){ // Does the queue contain queue_element
        if(head == nullptr) return 0;
        if(head->id == id) return 1;
        QueueElement * temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
            if(temp->id == id) return 1;
        }
        return 0;
    }


    int top(){ // Returns the top element of the queue
        return head->id;
    }

    int size(){ // Returns the number of queue_elements
        int size = 0;
        QueueElement * temp = head;
        while(temp != nullptr){
            size++;
            temp = temp->next;
        }
        return size;
    }

    private:
    QueueElement * head;
    QueueElement * cursor;
}; // End PriorityQueue class

class ShortestPath{
    public:
    ShortestPath(Graph graph, int u, int w):done(0), graph(graph), u(u), w(w){} // TODO: const en los argumentos tambien?

    // vertices(list<int> list){ // List of vertices in G(V, E)

    // }

    list<int> path(){ // Find shortest path between u-w and returns the sequence of vertices representing shortest path u-v1-v2-...-vn-w
        dijkstra(u);
        list<int> res;
        int aux = w;
        res.push_front(aux);
        while(aux != u){
            aux = prev[aux];
            res.push_front(aux);
        }
        return res;
    }

    double path_size(){ // Returns the path cost associated with the shortest path
        dijkstra(u);
        return dist[w];
    }

    void print(){
        list<int> path = this->path();
        for (auto it = path.cbegin(); it != path.cend(); it++){
            cout << *it;
            if(it != std::prev(path.end())) cout << " -> ";
        }

        cout << "\t\t" << path_size() << endl;
    }

    private:
    int done;
    Graph graph;
    const int u, w;
    vector<double> dist = vector<double>(graph.V());
    vector<int> prev = vector<int>(graph.V());

    void dijkstra(int inicio){
        if(done) return;
        int u = inicio;
        dist[u] = 0.0;    // Initialization
        PriorityQueue Q;
        for(int v = 0; v < graph.V(); v++){
            if(v != u){
                dist[v] = numeric_limits<double>::max();   // Unknown distance from source to v
                prev[v] = -1;   // Predecesor of v
            }
            Q.insert(v, dist[v]);
        }

        while(Q.size() != 0){   // The main loop
            u = Q.minPriority();    // Return best vertex and remove it
            vector<int> neighbors = graph.neighbors(u); // Only v that are still in Q
            for(auto const& v: neighbors){
                double alt = dist[u] + graph.get_edge_value(u, v);
                if(alt < dist[v]){
                    dist[v] = alt;
                    prev[v] = u;
                    Q.chgPriority(v, alt);
                }
            }
        }
        done = 1;
    }
}; // End ShortestPath class

int main(){
    Graph graph = Graph(randomMatrixGraph(50, 0.2, 1.0, 10.0));
    double avg = 0.0;
    for(int i = 1; i < 50; i++){
        ShortestPath sp = ShortestPath(graph, 0, i);
        // sp.print();
        avg += sp.path_size();
    }
    cout << "Average with density of 20%: " << avg/49 << endl;

    graph = Graph(randomMatrixGraph(50, 0.4, 1.0, 10.0));
    avg = 0.0;
    for(int i = 1; i < 50; i++){
        ShortestPath sp = ShortestPath(graph, 0, i);
        // sp.print();
        avg += sp.path_size();
    }
    cout << "Average with density of 40%: " << avg/49 << endl;
    return 0;
}