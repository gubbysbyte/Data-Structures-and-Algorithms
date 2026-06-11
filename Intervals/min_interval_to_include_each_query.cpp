#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        sort(intervals.begin(), intervals.end());

        int n = queries.size();

        // {query value, original index}
        vector<pair<int, int>> q;
        for (int i = 0; i < n; i++) {
            q.push_back({queries[i], i});
        }

        sort(q.begin(), q.end());

        vector<int> ans(n, -1);

        // {interval size, interval end}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        int i = 0;

        for (auto &[query, idx] : q) {

            // Add all intervals whose start <= query
            while (i < intervals.size() && intervals[i][0] <= query) {
                int left = intervals[i][0];
                int right = intervals[i][1];

                int size = right - left + 1;

                pq.push({size, right});
                i++;
            }

            // Remove intervals that cannot contain query
            while (!pq.empty() && pq.top().second < query) {
                pq.pop();
            }

            if (!pq.empty()) {
                ans[idx] = pq.top().first;
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> intervals = {{1, 4}, {2, 4}, {3, 6}, {4, 4}};
    vector<int> queries = {2, 3, 4, 5};

    vector<int> result = sol.minInterval(intervals, queries);

    cout << "Minimum intervals for each query: ";
    for (int ans : result) {
        cout << ans << " ";
    }
    cout << endl;

    return 0;
}