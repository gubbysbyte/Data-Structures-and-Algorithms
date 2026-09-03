class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int minEle = *min_element(begin(nums1), end(nums1)); //O(nlogn)

        if(minEle % 2 == 1){
            return true;
        }

        for(int &num : nums1){
            if(num % 2 == 1){
                return false;
            }
        }

        return true;
    }
};