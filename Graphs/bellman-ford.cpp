#include<bits/stdc++.h>
using namespace std;

// User function Template for C++

class Solution {
  public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
        // Code here
        vector<int> result(V, 1e8);
        result[src] = 0;
        
        for(int count = 0; count < V-1; count++){
            for(auto &edge: edges){
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];
                
                if(result[u] != 1e8 && result[u] + w < result[v]){
                    result[v] = result[u] + w;
                }
            }
        }
        
        // Now detect the cycle
        for(int count = 0; count < V-1; count++){
            for(auto &edge: edges){
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];
                
                if(result[u] != 1e8 && result[u] + w < result[v]){
                    return {-1};
                }
            }
        }
        return result;
    }
};



int main(){

    // Hardcoded input
    int V = 5; // Number of vertices
    int src = 0; // Source vertex

    vector<vector<int>> edges = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };

    Solution sol;
    vector<int> result = sol.bellmanFord(V, edges, src);

    if (result[0] == -1) {
        cout << "Negative weight cycle detected.\n";
    } else {
        cout << "Shortest distances from source vertex " << src << ":\n";
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << ": ";
            if (result[i] == 1e8) {
                cout << "Infinity\n";
            } else {
                cout << result[i] << "\n";
            }
        }
    }

    return 0;
}