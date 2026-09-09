#include <bits/stdc++.h>
using namespace std;

/*
 * Sum Segment Tree.
 *
 * Node i covers the array range [l, r].
 * Children of node i are  (2*i + 1)  and  (2*i + 2).
 * The tree needs at most 4*n nodes for an array of size n.
 */
class SegmentTree {
public:
    int n;                 // size of the underlying array
    vector<int> nums;      // current array values
    vector<int> segTree;   // tree nodes (each stores a range sum)

    explicit SegmentTree(const vector<int>& input) {
        nums = input;
        n = (int)nums.size();
        segTree.assign(4 * n, 0);
        if (n > 0) buildSegTree(0, 0, n - 1);
    }

    // Build node i so that it holds the sum of nums[l..r].
    void buildSegTree(int i, int l, int r) {
        if (l == r) {                 // leaf: covers a single element
            segTree[i] = nums[l];
            return;
        }

        int mid = l + (r - l) / 2;

        buildSegTree(2 * i + 1, l, mid);
        buildSegTree(2 * i + 2, mid + 1, r);

        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
    }

    // Public: sum of nums[ql..qr].
    int query(int ql, int qr) {
        return query(0, 0, n - 1, ql, qr);
    }

    int query(int i, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;             // no overlap
        if (ql <= l && r <= qr) return segTree[i];   // fully inside the query

        int mid = l + (r - l) / 2;
        return query(2 * i + 1, l, mid, ql, qr)
             + query(2 * i + 2, mid + 1, r, ql, qr);
    }

    // Public: set nums[pos] = val and refresh the tree.
    void update(int pos, int val) {
        update(0, 0, n - 1, pos, val);
    }

    void update(int i, int l, int r, int pos, int val) {
        if (l == r) {
            segTree[i] = val;
            nums[l] = val;
            return;
        }

        int mid = l + (r - l) / 2;
        if (pos <= mid) update(2 * i + 1, l, mid, pos, val);
        else            update(2 * i + 2, mid + 1, r, pos, val);

        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
    }
};

int main() {
    vector<int> nums = {1, 3, 5, 7, 9, 11};
    SegmentTree st(nums);

    cout << "sum[0..5] = " << st.query(0, 5) << "\n"; // 36
    cout << "sum[1..3] = " << st.query(1, 3) << "\n"; // 15

    st.update(2, 10);                                 // nums[2]: 5 -> 10
    cout << "after update nums[2] = 10\n";

    cout << "sum[0..5] = " << st.query(0, 5) << "\n"; // 41
    cout << "sum[1..3] = " << st.query(1, 3) << "\n"; // 20

    return 0;
}
