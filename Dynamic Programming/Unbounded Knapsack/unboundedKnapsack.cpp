#include<bits/stdc++.h>

using namespace std;

class Solution{
public:
    vector<vector<int>> dp;


// Top Down Approach
    int solveRec(int W, vector<int>& wt, vector<int>& val, int n){
        if(n == 0 || W == 0) return 0;

        if(dp[n][W] != -1) return dp[n][W];

        if(wt[n-1] <= W){
            return dp[n][W] = max(val[n-1] + solveRec(W - wt[n-1], wt, val, n), solveRec(W, wt, val, n -1));
        }
        else{
            return dp[n][W] = solveRec(W, wt, val, n -1);
        }
    }

// bottom up approach
    int solveRecBUA(int W, vector<int>& wt, vector<int>& val, int n){

        for(int i = 1; i < n + 1; i++){
            for(int j = 1; j < W + 1; j++){
                if(wt[i-1] <= j){
                    dp[i][j] = max(val[i-1] + dp[i][j - wt[i-1]], dp[i-1][j]);
                }
                else{
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[n][W];
    }

    int knapSack(int W, vector<int>& wt, vector<int>& val, int n){
        dp.assign(n + 1, vector<int>(W + 1, 0));
        return solveRecBUA(W, wt, val, n);
    }
};

int main(){
    int W = 100;
    vector<int> val = {10, 30, 20};
    vector<int> wt = {5, 10, 15};
    int n = val.size();

    Solution sol;
    cout << sol.knapSack(W, wt, val, n) << endl;
    return 0;
}