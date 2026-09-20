class Solution {
public:
    int reverseDegree(string s) {

        int sum = 0;

        for(int i = 0; i < s.length(); i++){
            int val = 'z' - s[i] + 1;
            int mul = val * (i+1);
            sum += mul;
        }
        return sum;
    }
};