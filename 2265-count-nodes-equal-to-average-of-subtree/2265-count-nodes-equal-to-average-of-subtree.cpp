/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    int ans = 0;

    pair<int, int> dfs(TreeNode *node){
        // base case
        if(!node) return {0,0};

        // normal case
        auto [left_subtree, left_count] = dfs(node->left);
        auto [right_subtree, right_count] = dfs(node->right);

        int sum = left_subtree + right_subtree + node->val;
        int count = left_count + right_count + 1;

        if(sum / count == node->val) ans++;

        return {sum, count};
    }


public:
    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};