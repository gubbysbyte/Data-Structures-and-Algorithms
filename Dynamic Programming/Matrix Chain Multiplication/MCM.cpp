#include<bits/stdc++.h>
using namespace std;

class Solution{

    vector<vector<int>> dp;

public: 

    int solve(vector<int> &arr, int i, int j){
        // Base Condition
        if(i >= j) return 0;

        //dp 2d array check
        if(dp[i][j] != -1) return dp[i][j];
 
        int mn = INT_MAX;
        for(int k = i; k < j; k++){
            int temp_ans = solve(arr, i, k) + solve(arr, k+1, j) + arr[i-1]*arr[k]*arr[j];
            if(temp_ans < mn){
                mn = temp_ans;
            } 
        }
        return dp[i][j] = mn;
    }

    int dpInititalisation(vector<int> &arr, int i, int j){
        int n = arr.size();
        dp.assign(n, vector<int>(n, -1));
        return solve(arr, i, j);
    }
};


int main(){
    vector<int> arr = {40, 30, 20, 10, 30};
    int n = arr.size();
    
    Solution sol;
    cout << sol.dpInititalisation(arr, 1, n - 1) << endl;
    return 0;
}