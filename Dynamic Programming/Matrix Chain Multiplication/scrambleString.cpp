#include<bits/stdc++.h>
using namespace std;

class Solution{
    unordered_map<string, int> mp;
public:
    bool solve(const string& a, const string& b){
        if(a.compare(b) == 0) return true;
        if(a.length() <= 1) return false;

        string key = a; //"a"
        key.push_back(' '); //"a "
        key.append(b); //"a b"
        if(mp.find(key) != mp.end()){
            return mp[key];
        }

        int n = a.length();
        bool flag = false;

        for(int i = 1; i <= n - 1; i++){
            if((solve(a.substr(0, i), b.substr(n-i, i)) && solve(a.substr(i, n-i), b.substr(0, n-i))) || (solve(a.substr(0, i), b.substr(0, i)) && solve(a.substr(i, n-i), b.substr(i, n-i)))){
                flag = true;
                break;
            }
        }
        return mp[key] = flag;
    }


};

int main(){
    vector<pair<string, string>> inputs = {
        {"great", "rgeat"},
        {"abcde", "caebd"},
        {"a", "a"}
    };
    
    Solution sol;
    for(auto &p : inputs) {
        string a = p.first;
        string b = p.second;
        if(a.length() != b.length()){
            cout << "Input: " << a << ", " << b << " -> " << 0 << endl;
        } else {
            cout << "Input: " << a << ", " << b << " -> " << sol.solve(a, b) << endl;
        }
    }
    return 0;
}