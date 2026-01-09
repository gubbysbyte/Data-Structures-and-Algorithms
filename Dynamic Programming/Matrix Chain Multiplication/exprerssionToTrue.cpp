#include<bits/stdc++.h>
using namespace std;

class Solution{

    vector<vector<vector<int>>> dp;

public: 

    int solve(string &arr, int i, int j, bool exp){
        // Base Condition
        if(i > j) return 0;
        if(i==j){
            if(exp == true){
                return arr[i] == 'T';
            }else{
                return arr[i] == 'F';
            }
        }

        //dp 2d array check
        if(dp[i][j][exp] != -1) return dp[i][j][exp];
 
        int ans = 0;

        for(int k = i + 1; k <= j-1; k+=2){
            int lt = solve(arr, i, k -1, true);
            int lf = solve(arr, i, k -1, false);
            int rt = solve(arr, k+1, j, true);
            int rf = solve(arr, k +1, j, false);

            if(arr[k] == '&'){
                if(exp == true){
                    ans = ans + lt*rt;
                }else{
                    ans = ans + lf*rt + lt*rf + lf*rf;
                }
            }
            else if(arr[k] == '|'){
                if(exp == true){
                    ans = ans + lt*rt + lt*rf + lf*rt;
                }else{
                    ans = ans + lf*rf;
                }
            }
            else if(arr[k] == '^'){
                if(exp == true){
                    ans = ans + lf*rt + lt*rf;
                }else{
                    ans = ans + lt*rt + lf*rf;
                }
            }
        }
        return dp[i][j][exp] = ans;
    }

    int dpInititalisation(string &arr, int i, int j){
        int n = arr.size();
        dp.assign(n, vector<vector<int>>(n, vector<int>(2, -1)));
        return solve(arr, i, j, true);
    }
};


int main(){
    vector<string> inputs = {
        "T|F&T",
        "T^F|F",
        "T|T&F^T"
    };
    
    Solution sol;
    for(string &arr : inputs) {
        int n = arr.length();
        cout << "Input: " << arr << " -> EXPRESSION: " << sol.dpInititalisation(arr, 0, n - 1) << endl;
    }
    return 0;
}