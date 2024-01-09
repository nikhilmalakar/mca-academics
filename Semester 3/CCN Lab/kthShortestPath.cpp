#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

typedef pair<int, int> pii; // (length, vertex)

const int INF = 1e9; // Infinity

vector<vector<pii>> adjList; // Adjacency list
vector<int> count; // To keep track of the number of paths found

void dijkstraKShortestPaths(int s, int t, int k) {
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    
    while (!q.empty()) {
        int l = q.top().first;
        int u = q.top().second;
        q.pop();
        
        if (count[u] == k) {
            continue;
        }
        
        //Counting the path node
        count[u]++;
        
        if (u == t) {
            cout << "Found a path of length " << l << endl;
        }
        
        for (auto edge : adjList[u]) {
            int v = edge.second;
            int w = edge.first;
            q.push({l + w, v});
        }
    }
}

int main() {
    int n, m, s, t, k;
    n = 6; // Number of vertices
    adjList.resize(n);
    count.assign(n, 0);
    
    int graph[n][n] = { 
					  {0,1,1,0,0,0},
                 	  {1,0,1,1,1,0},
					  {1,1,0,0,1,0},
					  {0,1,0,0,1,1},
					  {0,1,1,1,0,1},
					  {0,0,0,1,1,0}};
    
    for (int i = 0; i < n; i++) {
        for(int j=0; j<n; j++){
        	if(graph[i][j] != 0){
        		adjList[i].push_back({graph[i][j], j});
			}
		}
    }
    
//    for(int i=0; i<n; i++){
//    	for(auto x : adjList[i])
//    		cout<<x.second<<" ";
//    	cout<<endl;
//	}
    cout<<"Enter source vertex, destination vertex and K (Number of path required) : ";
    cin >> s >> t >> k; // Source, destination, and k
    
    dijkstraKShortestPaths(s, t, k);
    
    return 0;
}
