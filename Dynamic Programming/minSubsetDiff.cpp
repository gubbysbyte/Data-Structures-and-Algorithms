#include<bits/stdc++.h>

using namespace std;

class Solution{
public:
    vector<vector<int>> dp;

    bool solveRec(vector<int>& arr, int target, int n){
        if(target == 0) return true;
        if(n == 0) return false;

        if(dp[n][target] != -1) return dp[n][target];

        if(arr[n-1] <= target){
            return dp[n][target] = solveRec(arr, target - arr[n-1], n -1) || solveRec(arr, target, n -1);
        }
        else{
            return dp[n][target] = solveRec(arr, target, n -1);
        }
    }

    void solve(vector<int>& arr, vector<int>& sumStore, int n){
        for(int i = 0; i < sumStore.size(); ){
            int target = sumStore[i];
            dp.assign(n + 1, vector<int>(target + 1, -1));
            if(!solveRec(arr, target, n)){
                //remove current element from sumStore
                sumStore.erase(sumStore.begin() + i);
            } else {
                i++;
            }
        }
    }

    int mini(vector<int>& sumStore, int sum){
        int minimumNo = INT_MAX;
        for(int i = 0; i < sumStore.size(); i++){
            if(sumStore[i] <= sum / 2)
                minimumNo = min(minimumNo, sum - 2 * sumStore[i]);
        }
        return minimumNo;
    }
};

int main(){
    vector<int> arr = {1, 11, 5, 9};

    int n = arr.size();

    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += arr[i];
    }

    vector<int> sumStore;
    for(int i = 0; i <= sum; i++){
        sumStore.push_back(i);
    }
    
    Solution sol;
    sol.solve(arr, sumStore, n);
    
    cout <<sol.mini(sumStore, sum) << endl;

    // output - T || F
    return 0;
}