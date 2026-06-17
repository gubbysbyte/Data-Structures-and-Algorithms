// Find character at position k after processing string operations
// Operations: regular char = append, '*' = backspace, '#' = double, '%' = reverse
// Returns '.' if k is out of bounds

// Time Complexity: O(n)
// Space Complexity: O(1)

// Approach: reverse simulation — forward pass computes final length,
// backward pass traces which original character maps to position k

#include<iostream>
#include<string>
using namespace std;

class Solution {
public:
    char processStr(string s, long long k) {
        int n = s.size();
        long long L = 0;

        for(int i = 0; i < n; i++){
            if(s[i] == '*'){
                if(L > 0) L--;
            } else if(s[i] == '#'){
                L = 2 * L;
            } else if(s[i] == '%'){
                continue;
            } else{
                L++;
            }
        }

        if(k >= L){
            return '.';
        }

        for(int i = n - 1; i >= 0; i--){
            if(s[i] == '*'){
                L++;
            } else if(s[i] == '#'){
                L = L/2;
                k = (k >= L) ? k - L : k;
            } else if(s[i] == '%'){
                k = L - k - 1;
            } else{
                L--;
            }

            if(k == L){
                return s[i];
            }
        }
        return '.';
    }
};

int main(){
    Solution sol;

    // "ab#%c" → "ab" → "abab" → "baba" → "babac"
    // index:                                 01234
    cout << sol.processStr("ab#%c", 0) << "\n"; // 'b'
    cout << sol.processStr("ab#%c", 2) << "\n"; // 'b'
    cout << sol.processStr("ab#%c", 4) << "\n"; // 'c'

    // backspace: "abc*" → "ab"
    cout << sol.processStr("abc*", 1) << "\n"; // 'b'
    cout << sol.processStr("abc*", 2) << "\n"; // '.' (out of bounds)

    // k out of bounds
    cout << sol.processStr("a", 5) << "\n"; // '.'

    return 0;
}
