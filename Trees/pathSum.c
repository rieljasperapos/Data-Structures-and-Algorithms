/* Problem: return true if the sum of a path from root to a leaf node == Target number */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} *Tree;

bool hasPathSum(Tree T, int targetSum) {
    // Base case: an empty tree has no path
    if (T == NULL) {
        return false;
    }

    // Check if the current node is a leaf
    if (T->left == NULL && T->right == NULL) {
        return (targetSum - T->val) == 0;
    }

    // Recursively check left and right subtrees
    printf("Target Sum: %d\n", targetSum);
    bool leftPath = hasPathSum(T->left, targetSum - T->val);
    bool rightPath = hasPathSum(T->right, targetSum - T->val);

    // Return true if a path is found in either subtree
    return leftPath || rightPath;
}

int main() {
    // Hard coded example of a binary tree
    Tree root = NULL;
    root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = 6;

    root->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->val = 2;
    root->left->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->left->val = 8;
    root->left->left->left = NULL;
    root->left->left->right = NULL;
    root->left->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->right->val = 10;
    root->left->right->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->right->left->val = 14;
    root->left->right->left->left = NULL;
    root->left->right->left->right = NULL;
    root->left->right->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->right->right->val = 4;
    root->left->right->right->left = NULL;
    root->left->right->right->right = NULL;

    root->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->right->val = 12;
    root->right->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->right->left->val = 20;
    root->right->left->left = NULL;
    root->right->left->right = NULL;
    root->right->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->right->right->val = 30;
    root->right->right->right = NULL;
    root->right->right->left = NULL;

    int targetSum = 22;
    bool result = hasPathSum(root, targetSum);

    printf("Does the tree have a path with sum %d? %s\n", targetSum, result ? "true" : "false");

    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
