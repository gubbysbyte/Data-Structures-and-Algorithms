#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution{
public:
    vector<vector<int>> dp;

    int solveRec(vector<int>& arr, int target, int n){
        if(target == 0) return 1;
        if(n == 0) return 0;

        if(dp[n][target] != -1) return dp[n][target];

        if(arr[n-1] <= target){
            return dp[n][target] = solveRec(arr, target - arr[n-1], n -1) + solveRec(arr, target, n -1);
        }
        else{
            return dp[n][target] = solveRec(arr, target, n -1);
        }
    }

    int solve(vector<int>& arr, int target, int n){
        dp.assign(n + 1, vector<int>(target + 1, -1));
        return solveRec(arr, target, n);
    }
};

int main(){
    vector<int> arr = {2, 4, 6};

    int n = arr.size();
    int target = 7;
    // for(int i = 0; i < n; i++){
    //     sum += arr[i];
    // }

    // if(sum % 2 != 0) return false;
    Solution sol;
    cout << sol.solve(arr, target, n)  << endl;
    // output - T || F
    return 0;
}