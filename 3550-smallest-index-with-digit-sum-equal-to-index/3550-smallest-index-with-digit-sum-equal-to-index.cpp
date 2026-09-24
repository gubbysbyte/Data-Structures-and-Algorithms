class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        int smallest = INT_MAX;

        for(int i = 0; i < nums.size(); i++){
            string num = to_string(nums[i]);
            int eleSum = 0;
            for(int j = 0; j < num.length(); j++){
                eleSum += num[j] -'0';
            }
            if( i == eleSum){
                smallest = min(smallest, eleSum);
            }
        }

        return smallest == INT_MAX ? -1: smallest;
    }
};