#include<bits/stdc++.h>
using namespace std;

class Solution{

    vector<vector<int>> dp;

public: 
    bool isPalindrome(string &arr, int i, int j){
        if(i >= j) return true;
        while(i < j){
            if(arr[i] != arr[j]){
                return false;
            }
            i++;
            j--;
        }
        return true;
    }

    int solve(string &arr, int i, int j){
        // Base Condition
        if(i >= j) return 0;

        if(isPalindrome(arr, i, j)) return 0;

        //dp 2d array check
        if(dp[i][j] != -1) return dp[i][j];
 
        int mn = INT_MAX;

        for(int k = i; k < j; k++){
            int temp_ans = solve(arr, i, k) + solve(arr, k+1, j) + 1;
            if(temp_ans < mn){
                mn = temp_ans;
            } 
        }
        return dp[i][j] = mn;
    }

    int dpInititalisation(string &arr, int i, int j){
        int n = arr.size();
        dp.assign(n, vector<int>(n, -1));
        return solve(arr, i, j);
    }
};


int main(){
    vector<string> inputs = {
        "nitin", "abcde", "aab", "abacaba", "banana"
    };
    
    Solution sol;
    for(string &arr : inputs) {
        int n = arr.length();
        cout << "Input: " << arr << " -> Min Cuts: " << sol.dpInititalisation(arr, 0, n - 1) << endl;
    }
    return 0;
}