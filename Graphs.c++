/* Unit-IV Graphs: Representation of Graphs, Searching in Graphs – BFS and its applications, DFS
and its applications */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
using namespace std;

/////////////////////////////
// Graph using Adjacency List
/////////////////////////////
class GraphList {
    int V;
    vector<vector<int>> adj;

public:
    GraphList(int v) : V(v), adj(v) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // For undirected graph
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        cout << "BFS traversal: ";
        while (!q.empty()) {
            int node = q.front(); q.pop();
            cout << node << " ";
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    void DFSUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";
        for (int neighbor : adj[node]) {
            if (!visited[neighbor])
                DFSUtil(neighbor, visited);
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "DFS traversal: ";
        DFSUtil(start, visited);
        cout << endl;
    }

    void connectedComponents() {
        vector<bool> visited(V, false);
        int count = 0;
        cout << "Connected Components:\n";
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                cout << "Component " << ++count << ": ";
                DFSUtil(i, visited);
                cout << endl;
            }
        }
    }

    bool hasCycleUtil(int v, int parent, vector<bool>& visited) {
        visited[v] = true;
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                if (hasCycleUtil(neighbor, v, visited))
                    return true;
            } else if (neighbor != parent) {
                return true;
            }
        }
        return false;
    }

    bool hasCycle() {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++) {
            if (!visited[i] && hasCycleUtil(i, -1, visited))
                return true;
        }
        return false;
    }
};

/////////////////////////////
// Graph using Adjacency Matrix
/////////////////////////////
class GraphMatrix {
    int V;
    vector<vector<int>> matrix;

public:
    GraphMatrix(int v) : V(v), matrix(v, vector<int>(v, 0)) {}

    void addEdge(int u, int v) {
        matrix[u][v] = matrix[v][u] = 1;
    }

    void display() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

/////////////////////////////
// Main for Testing
/////////////////////////////
int main() {
    cout << "Graph with Adjacency List:\n";
    GraphList g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(4, 5); // Separate component

    g.BFS(0);
    g.DFS(0);
    g.connectedComponents();
    cout << "Has Cycle? " << (g.hasCycle() ? "Yes" : "No") << endl;

    cout << "\nGraph with Adjacency Matrix:\n";
    GraphMatrix gm(4);
    gm.addEdge(0, 1);
    gm.addEdge(0, 2);
    gm.addEdge(1, 2);
    gm.addEdge(2, 3);
    gm.display();

    return 0;
}
