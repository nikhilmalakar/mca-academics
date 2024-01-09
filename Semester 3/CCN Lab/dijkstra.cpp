// djisktra
#include <iostream>
#include <limits.h>

using namespace std;

int V;

//function to find the minimum distance in dist[] array
//and return its index
int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;
	
	// iterate over all the nodes
    for (int v = 0; v < V; v++)
		// if node is invisited and has lesser distance than min
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[])
{
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; i++)
        cout << i << " \t\t\t" << dist[i] << endl;
}

void dijkstra(int graph[100][100], int src)
{
    int dist[V]; // array to store all the distances 

    bool vis[V]; // array to track which nodes are visited

	// set the distance to infinte and visited to false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, vis[i] = false;

	// set distance between source to source as 0
    dist[src] = 0;
	
	// iterate over all nodes
    for (int count = 0; count < V - 1; count++)
    {
    	// get the current minimum distance from dist[] array
        int u = minDistance(dist, vis);

		// mark the minimum vertex as visited
        vis[u] = true;
		
		// iterate over all the unvisited nodes
        for (int v = 0; v < V; v++)
        	// if the current distance of node v is greater than 
			// the sum of distances of node u and edge u->v, update dist[v
            if (!vis[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

	// print the minimum distance between source and all other nodes
    printSolution(dist);
}

int main()
{
//	int V;
	cout << "Enter the number of vertices: ";
	cin >> V;
//    int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
//                       {4, 0, 8, 0, 0, 0, 0, 11, 0},
//                       {0, 8, 0, 7, 0, 4, 0, 0, 2},
//                       {0, 0, 7, 0, 9, 14, 0, 0, 0},
//                       {0, 0, 0, 9, 0, 10, 0, 0, 0},
//                       {0, 0, 4, 14, 10, 0, 2, 0, 0},
//                       {0, 0, 0, 0, 0, 2, 0, 1, 6},
//                       {8, 11, 0, 0, 0, 0, 1, 0, 7},
//                       {0, 0, 2, 0, 0, 0, 6, 7, 0}};
	int graph[100][100];
	for(int i = 0; i < V; i++)
		for(int j = 0; j < V; j++)
			cin >> graph[i][j];
	
	int src;
	cout << "Enter the source ";
	cin >> src;
    dijkstra(graph, src);
    return 0;
}