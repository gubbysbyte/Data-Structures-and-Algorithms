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

    int solveTDA(vector<int>& coin, int sum, int n){
        for(int i = 0; i < n + 1; i++){
            dp[i][0] = 1;
            // because at 0th sum, we have one way that is null set.
        }

        for(int i = 1; i < n+1; i++){
            for(int j = 1; j < sum+1; j++){
                if(coin[i - 1] <= j){
                    dp[i][j] = dp[i][j - coin[i - 1]] + dp[i - 1][j];
                }
                else{
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[n][sum];
    }

    int solve(vector<int>& coin, int sum, int n){
        dp.assign(n + 1, vector<int>(sum + 1, 0));
        int maximumProfit = solveTDA(coin, sum, n);
        return maximumProfit;
    }
};

int main(){ 
    vector<int> coin = {1, 2, 3};
    int sum = 5;

    // Finding total number of ways to get this sum!

    int n = coin.size();

    Solution sol;
    cout<< "Total number of ways : " << sol.solve(coin, sum, n) << endl;


    return 0;
}