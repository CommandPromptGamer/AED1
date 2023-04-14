// Lucas Superti da Silva, M1

#include <stdlib.h>
#include <stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int diameterOfBinaryTree(struct TreeNode* root);
int FindDown( struct TreeNode* branch );

int main() {
    struct TreeNode* root = malloc( sizeof( struct TreeNode ) );
    struct TreeNode* branch = root;
    
    branch->val = 10;

    for ( int i = 11; i < 20; i++ ) {
        branch->right = malloc( sizeof( struct TreeNode ) );
        branch = branch->right;

        branch->val = i;
        branch->left = NULL;
    }

    branch = root;

    for ( int i = 9; i > 0; i-- ) {
        branch->left = malloc( sizeof( struct TreeNode ) );
        branch = branch->left;

        branch->val = i;
        branch->right = NULL;
    }

    printf( "%d\n", diameterOfBinaryTree( root ) );

    return 0;
}

int diameterOfBinaryTree(struct TreeNode* root){
    int left  = 0;
    int right = 0;
    
    if ( root->left != NULL ) {
        left = FindDown( root->left );
    }

    if ( root->right != NULL ) {
        right = FindDown( root->right );
    }

    return right + left;
}

int FindDown( struct TreeNode* branch ) {
    int left;
    int right;

    if ( branch->left != NULL ) {
        left = FindDown( branch->left ) + 1;
    } else {
        left = 1;
    }

    if ( branch->right != NULL ) {
        right = FindDown( branch->right ) + 1;
    } else {
        right = 1;
    }

    return left > right ? left : right;
}