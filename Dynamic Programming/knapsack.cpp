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
        int dp[n][W];
        // base case changed to initialisation of the kanpsack
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == 0 || j == 0)
                {
                    dp[i][j] = 0;
                }
            }
        }

        for (int i = 1; i < n + 1; i++)
        {
            for (int j = 1; j < W + 1; j++)
            {
                if (wt[i - 1] <= j)
                {
                    dp[i][j] = max(val[i - 1] + dp[i - 1][j - wt[i - 1]], dp[i - 1][j]);
                }
                else
                {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][W];
    }
};

int main()
{
    vector<int> val = {60, 100, 120};
    vector<int> wt = {10, 20, 30};
    int W = 50;
    int n = val.size();

    Solution sol;
    cout << sol.knapSack(W, wt, val, n) << endl;
    return 0;
}
