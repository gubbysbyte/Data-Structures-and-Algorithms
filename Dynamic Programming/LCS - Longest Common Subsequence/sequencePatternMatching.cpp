#include<bits/stdc++.h>
using namespace std;

class Solution{
    vector<vector<int>> dp;
public:

//  Bottom-Up Approach (Recursive + Memoization)
    int lcsBUA(string &a, string &b, int n, int m){
        if(n == 0 || m == 0){
            return dp[n][m] = 0;
        }
        if(dp[n][m] != -1) return dp[n][m];

        if(a[n - 1] == b[m - 1]){
            return dp[n][m] = 1 + lcsBUA(a, b, n-1, m-1);
        }
        else{
            return dp[n][m] = max(lcsBUA(a, b, n-1, m), lcsBUA(a, b, n, m-1));
        }
        return dp[n][m];
    }

//  Top-Down Approach (Iterative / Tabulation)
    int lcsTDA(string &a, string &b, int n, int m){
        for(int i = 0; i < n + 1; i++){
            for(int j = 0; j < m + 1; j++){
                if(i == 0 || j == 0){
                    dp[i][j] = 0;
                }
            }
        }

        for(int i = 1; i < n + 1; i++){
            for(int j = 1; j < m + 1; j++){
                if(a[i - 1] == b[j - 1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                }
                else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        
        return dp[n][m];
    }


    int lcsInitialisation(string &a, string &b, int n, int m){
        dp.assign(n + 1, vector<int>(m + 1, -1));
        return lcsTDA(a, b, n, m);
    }
};

int main(){
    string a = "AXYZ";
    string b = "ACXCPY";

    int n = a.length();
    int m = b.length();

    Solution sol;
    int lcsLength = sol.lcsInitialisation(a, b, n, m);
    
    if(n == lcsLength){
        cout<<"True";
    }
    else{
        cout<<"False";
    }


    return 0;
}