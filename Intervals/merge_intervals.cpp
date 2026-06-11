#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};

        vector<vector<int>> res;

        sort(intervals.begin(), intervals.end());
        vector<int> temp = intervals[0];

        for(auto it: intervals){
            if(it[0] <= temp[1]){
                temp[1] = max(temp[1], it[1]);
            }
            else{
                res.push_back(temp);
                temp = it;
            }
        }
        res.push_back(temp);
        return res;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};

    cout << "Original intervals: [1, 3] [2, 6] [8, 10] [15, 18]\n";

    vector<vector<int>> merged = sol.merge(intervals);

    cout << "Merged intervals: ";
    for (const auto& interval : merged) {
        cout << "[" << interval[0] << ", " << interval[1] << "] ";
    }
    cout << endl;

    return 0;
}