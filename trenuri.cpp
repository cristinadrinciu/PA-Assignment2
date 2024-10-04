#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>

#define MAX_NAME 100

using namespace std;

ifstream fin("trenuri.in");
ofstream fout("trenuri.out");

// function to perform the topological sort
vector<string>  topologicalSort(unordered_map<string, vector<string>> adj,
                                    unordered_map<string, int> inDegree) {
    // create a queue to store the nodes with in-degree 0
    queue<string> q;

    // create a vector to store the sorted nodes
    vector<string> sorted;

    // add the nodes with in-degree 0 to the queue
    for (auto it : inDegree) {
        if (it.second == 0) {
            q.push(it.first);
        }
    }

    // while the queue is not empty
    while (!q.empty()) {
        // get the front element
        string u = q.front();
        q.pop();

        // add the node to the sorted list
        sorted.push_back(u);

        // for each neighbour of the node
        for (string v : adj[u]) {
            // decrement the in-degree of the neighbour
            inDegree[v]--;

            // if the in-degree of the neighbour is 0, add it to the queue
            if (inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // return the sorted vector
    return sorted;
}

// returns the longest path in the DAG from the departure to the arrival
int longestPath(unordered_map<string, vector<string>> adj,
                vector<string> sorted, string departure, string arrival) {
    // create a map to store the distances from the departure to each node
    unordered_map<string, int> dist;

    // set the distance of the departure to 1, since it is the starting point
    dist[departure] = 1;

    // for each node in the sorted list
    for (string u : sorted) {
        // for each neighbour of the node
        for (string v : adj[u]) {
            // if the distance of the neighbour is smaller
            // than the distance of the current node + 1
            if (dist.find(u) != dist.end() && dist[v] < dist[u] + 1) {
                dist[v] = dist[u] + 1;
            }
        }
    }

    // return the distance of the arrival
    return dist[arrival];
}

int main() {
    char departure[MAX_NAME], arrival[MAX_NAME];

    fin >> departure >> arrival;

    int m;

    fin >> m;

    // declare the adjacency list of the DAG

    unordered_map<string, vector<string>> adj;
    unordered_map<string, int> inDegree;


    for (int i = 0; i < m; i++) {
        char station1[MAX_NAME], station2[MAX_NAME];

        fin >> station1 >> station2;

        // add the edge to the adjacency list

        adj[station1].push_back(station2);

        // increment the in-degree of the arrival station
        inDegree[station2]++;

        // check if the first station has an in-degree
        if (inDegree.find(station1) == inDegree.end()) {
            inDegree[station1] = 0;
        }
    }

    // topological sort
    vector<string> sorted = topologicalSort(adj, inDegree);

    // get the longest path
    int longest = longestPath(adj, sorted, departure, arrival);

    fout << longest << endl;

    return 0;
}
