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
    string lcsTDA(string &a, string &b, int n, int m){
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

        int i = n, j = m;
        string s = "";
        while(i > 0 && j > 0){
            if(a[i-1] == b[j - 1]){
                s.push_back(a[i - 1]);
                i--;
                j--;
            }
            else{
                if(dp[i-1][j] > dp[i][j-1]){
                    i--;
                }
                else{
                    j--;
                }
            }
        }
        reverse(s.begin(), s.end());
        return s;
    }


    string lcsInitialisation(string &a, string &b, int n, int m){
        dp.assign(n + 1, vector<int>(m + 1, -1));
        return lcsTDA(a, b, n, m);
    }
};

int main(){
    string a = "agbcba";
    string b = a;
    reverse(b.begin(), b.end());

    int n = a.length();
    int m = n;

    Solution sol;
    string lps = sol.lcsInitialisation(a, b, n, m);
    
    string deleted = "";
    int i = 0, j = 0;
    while(i < n){
        if(j < lps.length() && a[i] == lps[j]){
            j++;
        } else {
            deleted += a[i];
        }
        i++;
    }
    
    cout << "Deleted characters: " << deleted << endl;

    return 0;
}