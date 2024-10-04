#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

#define MODULO 1000000007

using namespace std;

ifstream fin("numarare.in");
ofstream fout("numarare.out");

int main() {
    int N, M;

    fin >> N >> M;

    // each graph is represented by N + 1 vectors of unordered sets
    vector<unordered_set<int>> graph1(N + 1);

    // read the edges of the first graph
    for (int i = 0; i < M; i++) {
        int u, v;
        fin >> u >> v;

        graph1[u].insert(v);
    }

    vector<unordered_set<int>> commonEdges(N + 1);
    // read the edges of the second graph and store the common edges
    for (int i = 0; i < M; i++) {
        int u, v;
        fin >> u >> v;

        // check if the edge is common
        if (graph1[u].find(v) != graph1[u].end()) {
            commonEdges[u].insert(v);
        }
    }

    // calculate the number of paths from node 1 to node N in the common graph
    vector<int> dp(N + 1, 0);  // dp[i] = number of paths from node 1 to node i

    dp[1] = 1;  // base case

    for (int u = 1; u <= N; u++) {
        for (int v : commonEdges[u]) {
            // the number of ways to v is the sum between the current value and
            // the number of ways to u
            dp[v] = (dp[v] + dp[u]) % MODULO;
        }
    }

    // output the result
    fout << dp[N] << "\n";
}
