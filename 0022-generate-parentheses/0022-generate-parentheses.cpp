class Solution {
public:

    void solve(vector<string> &ans, int n, int open, int close, string cur_str){
        if(cur_str.length() == n * 2){
            ans.push_back(cur_str);
            return;
        }

        if(open < n) solve(ans, n, open + 1, close, cur_str + "(");
        if(close < open) solve(ans, n, open, close + 1, cur_str + ")");
    }

    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        solve(ans, n, 0, 0, "");
        return ans;
    }
};