#include<bits/stdc++.h>
using namespace std;

class NumArray {
public:
    int n;
    vector<int> segTree;

    void buildSegTree(int i, int l, int r, vector<int> & nums){
        // base Case
        if(l == r){
            segTree[i] = nums[r];
            return;
        }

        // normal case
        int mid = l + (r - l) / 2;
        buildSegTree(2*i + 1, l, mid, nums);
        buildSegTree(2*i + 2, mid + 1, r, nums);

        segTree[i] = segTree[2*i + 1] + segTree[2*i + 2];
    }

    void updateSegTree(int index, int val, int i, int l, int r){
        // Base Case
        if(l == r){
            segTree[i] = val;
            return;
        }

        // Normal Case
        int mid = l + (r - l) / 2;

        if(index <= mid){
            updateSegTree(index, val, 2 * i + 1, l, mid);
        } else {
            updateSegTree(index, val, 2 * i + 2, mid + 1, r);
        }

        segTree[i] = segTree[2*i + 1] + segTree[2*i + 2];
    }

    int querySegtree(int left, int right, int i, int l, int r){
        // base caase
        if(l > right || r < left){
            return 0;
        }
        if(l >= left && r <= right) return segTree[i];
        int mid = l + (r - l) / 2;
        return querySegtree(left, right, 2 * i + 1, l, mid) + querySegtree(left, right, 2 * i + 2, mid + 1, r);
    }

    NumArray(vector<int> nums){
        n = nums.size();
        segTree.resize(4*n);
        buildSegTree(0, 0, n - 1, nums);
    }

    void update(int index, int val){
        updateSegTree(index, val, 0, 0, n -1);
    }

    int sumRange(int left, int right){
        return querySegtree(left, right, 0, 0, n - 1);
    }


};

int main(){
    // LeetCode 307 sample: ["NumArray","sumRange","update","sumRange"]
    //                      [[[1,3,5]],   [0,2],     [1,2],    [0,2]]
    // Expected:            [null,        9,         null,     8]
    vector<int> nums = {1, 3, 5};
    NumArray na(nums);

    cout << "sumRange(0, 2)            = " << na.sumRange(0, 2) << "\n";   // 9  = 1 + 3 + 5
    na.update(1, 2);                                                      // nums -> {1, 2, 5}
    cout << "sumRange(0, 2) after update = " << na.sumRange(0, 2) << "\n"; // 8  = 1 + 2 + 5

    // extra checks
    cout << "sumRange(1, 2)            = " << na.sumRange(1, 2) << "\n";   // 7  = 2 + 5
    cout << "sumRange(0, 0)            = " << na.sumRange(0, 0) << "\n";   // 1
    cout << "sumRange(2, 2)            = " << na.sumRange(2, 2) << "\n";   // 5

    return 0;
}