class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        vector<long long> cnt(n + 1), tot(n + 1);  // Fenwick trees over previous-copy positions, stored right to left
        unordered_map<int, int> last;
        long long ans = 0;
        for (int r = 0; r < n; r++) {
            int p = last.count(nums[r]) ? last[nums[r]] : -1;
            long long c = 0, s = 0;
            for (int i = n - p - 1; i > 0; i -= i & -i)  // boxes 1..n-p-1 hold the positions > p
                c += cnt[i], s += tot[i];
            ans += (long long)(n - r) * ((long long)(r - p) * (r - p) - 2 * (s - p * c));
            for (int i = n - p; i <= n; i += i & -i)  // insert p; p = -1 lands past the end and is skipped
                cnt[i]++, tot[i] += p;
            last[nums[r]] = r;
        }
        return ans;
    }
};