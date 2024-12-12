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
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*>que;
        vector<vector<int>> result;
        if (root != nullptr) que.push(root);
        while (!que.empty()) {
            vector<int>vec;
            int size = que.size();
            while (size--) {
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (node->left) {
                    que.push(node->left);
                }
                if (node->right) {
                    que.push(node->right);
                }
            }
            result.push_back(vec);
        }
        return result;
    }
};
