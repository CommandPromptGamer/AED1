// Lucas Superti da Silva, M1

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int diameterOfBinaryTree(struct TreeNode* root);
int FindDown( struct TreeNode* branch );
void FillTreeRandomly( struct TreeNode** root );

int main() {
    struct TreeNode* root = NULL;

    srand( time( NULL ) );

    for( int i = 0; i < 100; i++ ) {
        FillTreeRandomly( &root );
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

void FillTreeRandomly( struct TreeNode** root ) {
    if ( *root == NULL ) {
        *root = malloc( sizeof( struct TreeNode ) );

        ( *root )->val = rand() % 201 - 100;
        ( *root )->left = NULL;
        ( *root )->right = NULL;
    } else if ( ( ( *root )->left == NULL && ( *root )->right == NULL ) || ( ( *root )->left != NULL && ( *root )->right != NULL ) ) {
        rand() > RAND_MAX / 2 ? FillTreeRandomly( &( *root )->left ) : FillTreeRandomly( &( *root )->right );
    } else {
        ( *root )->left == NULL ? FillTreeRandomly( &( *root )->left ) : FillTreeRandomly( &( *root )->right );
    }
}