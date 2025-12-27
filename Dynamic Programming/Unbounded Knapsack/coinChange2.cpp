#include<bits/stdc++.h>
using namespace std;

class Solution{
    vector<vector<int>> dp;

public:
    int solveTDA(vector<int>& coin, int sum, int n){

        // initialising first col with 0
        for(int i = 0; i < n + 1; i++){
            dp[i][0] = 0;
            // because at 0th sum, we have one way that is null set.
        }

        for(int i = 1; i < n+1; i++){
            for(int j = 1; j < sum+1; j++){
                if(coin[i - 1] <= j){
                    dp[i][j] = min(1 + dp[i][j - coin[i - 1]], dp[i - 1][j]);
                }
                else{
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[n][sum];
    }

    int solve(vector<int>& coin, int sum, int n){
        dp.assign(n + 1, vector<int>(sum + 1, INT_MAX - 1));
        int maximumProfit = solveTDA(coin, sum, n);
        return maximumProfit;
    }
};

int main(){ 
    vector<int> coin = {1, 2, 3, 4};
    int sum = 9;

    // Finding minimum number of coins required to make a solution.

    int n = coin.size();

    Solution sol;
    cout<< "Minimum number of coins required to give sum : " << sol.solve(coin, sum, n) << endl;

    // The ans should be 2, because 2+3 is a possibility and minimum number of coins to give you a 


    return 0;
}