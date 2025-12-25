#include<bits/stdc++.h>

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
    vector<int> arr = {1, 1, 2, 3};
    int diff = 1;

    int n = arr.size();
    int sum = 0;

    for(int i = 0; i < n; i++){
        sum += arr[i];
    }

    if ((diff + sum) % 2 != 0) {
        cout << 0 << endl;
        return 0;
    }

    int target = (diff + sum)/2;

    Solution sol;
    cout << sol.solve(arr, target, n) << endl;
    return 0;
}