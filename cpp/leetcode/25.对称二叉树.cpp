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
    bool compare(TreeNode* node1, TreeNode* node2) {
        if (node1 == nullptr && node2 != nullptr) return false;
        else if (node1 != nullptr && node2 == nullptr) return false;
        else if (node1 == nullptr && node2 == nullptr) return true;
        else if (node1->val != node2->val) return false;
        bool outside = compare(node1->left, node2->right);
        bool inside = compare(node1->right, node2->left);
        bool result = outside && inside;
        return result;
    }
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        return compare(root->left, root->right);
    }
};