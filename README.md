Drinciustina 324CA

## Problem 1 - Numarare

For solving this problem, I used the dynamic programming approach.
* read the edges of the first graph to store it
* read the edges of the second graph and store just the common edges with the first one (there is no need for storing the second graph)
* we will work just with the common graph
  * why? : because the common chains of the graphs are included in the commono graph
  * finding the number of ways from node 1 to node N will represent the number of common chains
* use a vector dp for dynamic programming
  * dp[i] = number of paths from node 1 to node i
  * for each node in the commong graph, take each neighbour and update the number of path to it
    * dp[neghbour] = (dp[neighbour] + dp[curr_node]) % MODULO (1000000007)
* the number of common chains is represented by dp[n]

### Time complexity: O(M + N) or O(V + E)
### Space complexity: O(M + N) or O(V + E)


## Problem 2 - Trenuri

This problem can be reduced to a DAG (directed acyclic graph), where the noes are the cities.
For solving it I used graphs:
* read the edges (the connections between the cities) and increment the in-degree of the arival station
* based on the in-degrees that were calculated, make a topological sort of the DAG graph
    * the topological sort will help us to find the longest path to the departure station to the arrival one
* calculate the longest path
    * use a map to store the distances from the departure node to each node of the graph
    * for each node in the sorted list of the stations, take each neighbour and update the distance of the neighbour if its current distance is smaller than the one of the current node + 1
* in the end, the longest path to the departure station to the arrival one is the dist[arrival].

### Time complexity: O(V + E) or O(M + adj.size()) (adj is the map where there are stored the routes between cities)
### Space complexity: O(V + E) or O(M + adj.size()) (adj is the map where there are stored the routes between cities)


## Problem 3 - Drumuri

For solving this problem I used most of it the Dijkstra's algorithm: the subset of edges with minimum cost will be represented by the minimum path from x to z and from y to z, but trying as much as possible to take the common edges just once
* read the edges of the graph and the 3 nodes that are the scope of this problem
* while reading the edges also build the reversed graph for later use
* apply Dijkstra's algorithm for each node x and y and also for z but on the reversed graph
  * by appply the Diskstra's algorithm on node z on the reversedd graph, we get the minimum path to each node
* calculate the best route with the minimum cost, by parsing each node:
  * because we applied Diskstra's algorithm also on z, the easiest way to find the minim cost is to find an intermediate node for each 3 nodes x, y and z
  * if there are path from x to i, from y to i and from z to i, update the cost if it is smaller than the current one
  * basically, take the best route with the minimum cost where a node i is intermediate for all 3 x, y, and z nodes.

### Time complexity: O((N+M)logN)
### Space complexity: O(N + M)
