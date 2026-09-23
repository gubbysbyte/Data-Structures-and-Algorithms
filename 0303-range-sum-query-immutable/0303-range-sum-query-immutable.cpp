class NumArray {
public:
    int n;
    vector<int> segTree;

    void buildSegTree(int i, int l, int r, vector<int> &nums){
        // base case
        if(l == r){
            segTree[i] = nums[r];
            return;
        }

        // normal case 
        int mid = l + (r - l)/2;
        buildSegTree(2*i+1, l, mid, nums);
        buildSegTree(2*i+2, mid + 1, r, nums);
        segTree[i] = segTree[2*i+1] + segTree[2*i+2];    
        
    }

    int calSumRange(int start, int end, int i, int l, int r){
        


        // out of range
        if(l > end || start > r){
            return 0;
        }

        // inside the range
        if(l >= start && r <= end){
            return segTree[i];
        }

        // overlapping situations
        int mid = l + (r - l) / 2;
        return calSumRange(start, end, 2*i+1, l, mid) + calSumRange(start, end, 2*i+2, mid + 1, r);
    }

    NumArray(vector<int>& nums) {
        n = nums.size();
        segTree.resize(4*n);
        buildSegTree(0, 0, n - 1, nums);
    }
    
    int sumRange(int left, int right) {
        return calSumRange(left, right, 0, 0, n-1);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */