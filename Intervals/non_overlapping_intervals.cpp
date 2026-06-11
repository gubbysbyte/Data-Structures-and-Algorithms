#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Time Complexity: O(n log n) due to sorting the intervals
    // Space Complexity: O(1) auxiliary (ignoring the space required for the sorting algorithm stack)
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        sort(intervals.begin(), intervals.end(),
            [](const vector<int> & a, const vector<int> &b){
                return a[1] < b[1];
            });
        
        int removeCount = 0;
        int lastEnd = intervals[0][1];

        for(int i = 1; i < intervals.size(); i++){
            if(intervals[i][0] < lastEnd){
                removeCount++;
            } else{
                lastEnd = intervals[i][1];
            }
        }
        return removeCount;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> intervals = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};

    cout << "Original intervals: [1, 2] [2, 3] [3, 4] [1, 3]\n";

    int removed = sol.eraseOverlapIntervals(intervals);

    cout << "Minimum intervals to remove: " << removed << endl;

    return 0;
}