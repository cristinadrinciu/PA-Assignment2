#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <queue>
#include <limits>

#define INF numeric_limits<long long>::max()

using namespace std;

ifstream fin("drumuri.in");
ofstream fout("drumuri.out");

typedef pair<long long, int> pli;  // pair (distance's cost, node)

// Dijkstra's algorithm
vector<long long> dijkstra(vector<vector<pli>>& adj, int start) {
    // vector to store the distances from the start node to all the other nodes
    vector<long long> dist(adj.size(), INF);

    // priority queue to store the nodes to be processed
    priority_queue<pli, vector<pli>, greater<pli>> pq;

    dist[start] = 0;  // the distance from the start node to itself is 0
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;  // the node with the smallest distance
        long long d = pq.top().first;  // the distance from the start node to u
        pq.pop();

        if (d > dist[u]) {
            // if the distance from the start node to u is greater than
            // the distance stored in the dist vector, we skip the node
            continue;
        }

        for (auto& edge : adj[u]) {
            int v = edge.second;
            long long w = edge.first;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    // mark -1 the nodes that are not reachable from the start node
    for (int i = 1; i < dist.size(); i++) {
        if (dist[i] == INF) {
            dist[i] = -1;
        }
    }

    return dist;
}

int main() {
    int N, M;

    fin >> N >> M;

    // vectors to store the adjacency list of the graph and its reversed version
    vector<vector<pli>> adj(N + 1);
    vector<vector<pli>> reversedAdj(N + 1);

    // read the edges of the graph
    for (int i = 0; i < M; i++) {
        int u, v;
        long long w;
        fin >> u >> v >> w;

        adj[u].push_back({w, v});
        reversedAdj[v].push_back({w, u});
    }

    int x, y, z;
    fin >> x >> y >> z;

    // run Dijkstra's algorithm on the graph and its reversed version
    vector<long long> distX = dijkstra(adj, x);
    vector<long long> distY = dijkstra(adj, y);
    vector<long long> distZ = dijkstra(reversedAdj, z);

    long long minCost = 0;

    // find the minimum cost of a subset of edges that include
    // a path from x to z and a path from y to z
    for (int i = 1; i <= N; i++) {
        // if there is a path from x to i, from y to i and from z to i
        if (distX[i] != -1 && distY[i] != -1 && distZ[i] != -1) {
            long long cost = distX[i] + distY[i] + distZ[i];
            if (minCost == 0 || cost < minCost) {
                minCost = cost;
            }
        }
    }

    fout << minCost << endl;

    return 0;
}
