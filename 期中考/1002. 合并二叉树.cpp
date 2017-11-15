#include <iostream>
#include <vector>
using namespace std;

//Definition for a binary tree node.
struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
//       TreeNode* merge(TreeNode* T1, TreeNode* T2) {
//             
//    }
};

TreeNode* merge(TreeNode* T1, TreeNode* T2) {
    // 都是空 
    if (T1 == NULL && T2 == NULL)  return NULL;
    // T1不为空 
    else if (T1 != NULL && T2 == NULL) {
        TreeNode *root = new TreeNode(T1->val);
        root->left = T1->left;
        root->right = T1->right;
        return root;
    }
    // T2不为空 
    else if (T1 == NULL && T2 != NULL) {
        TreeNode *root = new TreeNode(T2->val);
        root->left = T2->left;
        root->right = T2->right;
        return root;
    }
    
    // T1, T2都不为空 
    TreeNode *root = new TreeNode(T1->val + T2->val);
    root->left = merge(T1->left, T2->left);
    root->right = merge(T1->right, T2->right);
    return root;
}

void addTestData(vector<int> &A) {
    int data[100] = {2, 7, -2};
    int n = 3;
    for (int i = 0; i < n; i++)
        A.push_back(data[i]);
}

void showOutput(int output) {
    cout << output << endl;
}

int main() {
    vector<int> test;
    addTestData(test);
    //showOutput(minDifference(test)); 
}
