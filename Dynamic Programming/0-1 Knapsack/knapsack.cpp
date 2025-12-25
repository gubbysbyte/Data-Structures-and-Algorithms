#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    // Returns the maximum value that can be put in a knapsack of capacity W
    int knapSack(int W, vector<int> &wt, vector<int> &val, int n)
    {
        // Use vector for dynamic sizing and initialization to 0. Size is (n+1)x(W+1).
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, -1));

        // Bottom-Up Approach (Recursive and memoization)
        //Base Case
        if(n == 0 || W == 0){
            return 0;
        }

        if(dp[n][W] != -1) return dp[n][W];

        if(wt[n-1] <= W){
            return dp[n][W] = max(val[n - 1] + knapSack(W - wt[n -1], wt, val, n - 1), knapSack(W, wt, val, n - 1));
        }
        else if(wt[n - 1] > W){
            return dp[n][W] = knapSack(W, wt, val, n - 1);
        }

        // for (int i = 1; i <= n; i++)
        // {
        //     for (int j = 0; j <= W; j++)
        //     {
        //         if (wt[i - 1] <= j)
        //         {
        //             dp[i][j] = max(val[i - 1] + dp[i - 1][j - wt[i - 1]], dp[i - 1][j]);
        //         }
        //         else
        //         {
        //             dp[i][j] = dp[i - 1][j];
        //         }
        //     }
        // }
        return dp[n][W];

    }
};

int main()
{
    vector<int> val = {60, 100, 120};
    vector<int> wt = {1, 2, 3};
    int W = 5;
    int n = val.size();

    Solution sol;
    cout << sol.knapSack(W, wt, val, n) << endl;
    return 0;
}
