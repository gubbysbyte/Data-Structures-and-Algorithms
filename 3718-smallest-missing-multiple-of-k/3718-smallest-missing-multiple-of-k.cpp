class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {

        int n = nums.size();
        vector<int> store(102, -1);

        for(int i = 0; i < store.size(); i++){
            cout << store[i] << " ";
        }

        for(int i = 0; i < n; i++){
            if(nums[i] % k == 0){
                store[nums[i]/k] = nums[i];
            }else{
                continue;
            }
        } 
        cout << endl;
        for(int i = 0; i < store.size(); i++){
            cout << store[i] << " ";
        }

        for(int i = 1; i < store.size(); i++){
            if(store[i] == -1){
                return k * i;
            }
        }
        return -1;
    }
};