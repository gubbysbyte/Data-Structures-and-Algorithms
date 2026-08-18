class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        unordered_map<int, int> count;

        int n = nums.size();

        //Generate every subarray of size k
        for(int i = 0; i <= n - k; i++){
            unordered_set<int> seen;

            //Traverse current window
            for(int j = i; j < i + k; j++){
                seen.insert(nums[j]); 
            }

            //Each distinct number appears in this subarray
            for(int x: seen){
                count[x]++;
            }
        }

        //Find larget number appearing in exactly one subarray
        int ans = -1;
        
        for(auto [x, freq] : count) {
            if(freq == 1){
                ans = max(ans, x);
            }
        }
        return ans;
    }
};