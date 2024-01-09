
// disjoint paths
#include <bits/stdc++.h>

using namespace std;

vector<pair<vector<int>, vector<int>>> disjoint_paths(vector<vector<int>> paths){
	vector<pair<vector<int>, vector<int>>> ans;
	
	for(int i = 0; i < paths.size(); i++){
		set<int> st;
		for(int j = 1; j < paths[i].size(); j++) if(j != paths[i].size() - 1) st.insert(paths[i][j]);
		
		for(int j = i + 1; j < paths.size(); j++){
			bool flag = true;
			for(int k = 1; k < paths[j].size(); k++){
				if(st.find(paths[j][k]) != st.end()){
					flag = false;
					break;
				}
			}
			if(flag) ans.push_back({paths[i], paths[j]});
		}
	}
	
	return ans;
}

void dfs(vector<vector<int>> &graph, vector<vector<int>>& answer, vector<int> &path, vector<bool> &vis, int idx){
	path.push_back(idx);
	vis[idx] = true;
    if(idx == graph.size() - 1) answer.push_back(path);
    else{
        for(auto &v : graph[idx]){
        	if(not vis[v])
            	dfs(graph, answer, path, vis, v);
        }
    }
    vis[idx] = false;
    path.pop_back();
}

vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    vector<vector<int>> answer;
    int pathWt;
    vector<int> path;
    vector<bool> vis(graph.size() - 1, false);
    dfs(graph, answer, path, vis, 0);
    return answer;
}

int main(){
	int N;
	cout << "Enter number of nodes: "; cin >> N;
	int E;
	cout << "Enter the number of edges: "; cin >> E;
	vector<vector<int>> graph(N);
	while(E--){
		int u, v;
		cout << "Enter edge in the following format: u v ";
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	auto res = allPathsSourceTarget(graph);
	auto ans = disjoint_paths(res);
	
	cout << "The disjoint paths in the graph are : \n";
	for(auto a : ans){
		cout << "[";
		for(auto p1 : a.first) cout << p1 << " ";
		cout << "], [";
		for(auto p1 : a.second) cout << p1 << " ";
		cout << "]\n";
	}
	
	return 0;
}