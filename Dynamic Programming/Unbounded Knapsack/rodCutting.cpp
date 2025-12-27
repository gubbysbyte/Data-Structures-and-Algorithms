#include<bits/stdc++.h>
using namespace std;

class Solution{

    vector<vector<int>> dp;

public:
    int solveBUA(vector<int>& length, vector<int> &price, int N, int n){
        if(n == 0 || N == 0){
            return 0;
        }
        if(dp[n][N] != -1) return dp[n][N];

        if(length[n - 1] <= N){
            return dp[n][N] = max(price[n-1] + solveBUA(length, price, N - length[n-1], n), solveBUA(length, price, N, n -1));
        }
        else{
            return dp[n][N] = solveBUA(length, price, N, n-1);
        }
    }

    int solveTDA(vector<int>& length, vector<int> &price, int N, int n){
        for(int i = 0; i < n + 1; i++){
            for(int j = 0; j < N + 1; j++){
                if(i == 0 || j == 0) dp[i][j] = 0; 
            }
        }

        for(int i = 1; i < n+1; i++){
            for(int j = 1; j < N+1; j++){
                if(length[i - 1] <= j){
                    dp[i][j] = max(price[i - 1] + dp[i][j - length[i - 1]], dp[i - 1][j]);
                }
                else{
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[n][N];
    }

    int solve(vector<int>& length, vector<int> &price, int N, int n){
        dp.assign(n + 1, vector<int>(N + 1, -1));
        int maximumProfit = solveTDA(length, price, N, n);
        return maximumProfit;
    }
};

int main(){
    vector<int> length = {1, 2, 3, 4};
    vector<int> price = {1, 5, 8, 9};
    int N = 4;

    int n = price.size();

    Solution sol;
    cout<< "Maximum profit : " << sol.solve(length, price, N, n) << endl;


    return 0;
}