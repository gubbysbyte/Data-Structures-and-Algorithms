class Solution {
public:
    int countCommas(int n) {
        if(n < 1000) return 0;

        int count = 0;
        for(int i = 1000; i <= n; i++){
            count += 1;
        }

        return count;
    }
};