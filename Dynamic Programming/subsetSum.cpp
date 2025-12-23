#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;



class Solution{
public:

    vector<vector<int>> dp;


    bool solveRec(vector<int>& arr, int target, int n){
        // Base case
        if(target == 0) return true;
        if(n == 0) return false;

        if(dp[n][target] != -1) return dp[n][target];

        //recursive calls
        if(arr[n-1] <= target){
            return dp[n][target] = solveRec(arr, target - arr[n-1], n -1) || solveRec(arr, target, n -1);
        }
        else if(arr[n - 1] > target){
            return dp[n][target] = solveRec(arr, target, n -1);
        }

        // Top-Down Approach
        
        // Base Case: If target is 0, then answer is true (empty subset)
        // for (int i = 0; i <= n; i++) dp[i][0] = true;

        // for(int i = 1; i <= n; i++){
        //     for(int j = 1; j <= target; j++){
        //         if(arr[i-1] <= j){
        //             dp[i][j] = dp[i - 1][j-arr[i-1]] || dp[i-1][j];
        //         }
        //         else{
        //             dp[i][j] = dp[i-1][j];
        //         }
        //     }
        // }

        // return dp[n][target];
    }

    bool solve(vector<int>& arr, int target, int n){
        dp.assign(n + 1, vector<int>(target + 1, -1));
        return solveRec(arr, target, n);
    }
};

int main(){
    vector<int> arr = {2, 3, 7};
    int target = 5;

    int n = arr.size();

    Solution sol;
    cout << (sol.solve(arr, target, n) ? "true" : "false") << endl;

    // output - T || F
    return 0;
}