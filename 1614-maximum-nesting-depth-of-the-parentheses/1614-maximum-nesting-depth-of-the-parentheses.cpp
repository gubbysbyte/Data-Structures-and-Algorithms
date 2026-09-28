class Solution {
public:
    int maxDepth(string s) {
        int calc_num = 0;
        int max_num = 0;
        for(auto &i : s){
            if(i == '(') calc_num += 1;
            if(i == ')') calc_num--;
            if(calc_num > max_num) max_num = calc_num;
        }

        return max_num;
    }
};