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

int maximum = 0;  // Global maximum variable

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
    FindDown( root );

    return maximum;
}

int FindDown( struct TreeNode* branch ) {
    int left;
    int right;

    if ( branch->left != NULL ) {
        left = FindDown( branch->left );
    } else {
        left = 0;
    }

    if ( branch->right != NULL ) {
        right = FindDown( branch->right );
    } else {
        right = 0;
    }

    maximum = left + right > maximum ? left + right : maximum;
    return 1 + ( left > right ? left : right );
}

void FillTreeRandomly( struct TreeNode** root ) {
    if ( *root == NULL ) {
        *root = malloc( sizeof( struct TreeNode ) );

        ( *root )->val = rand() % 201 - 100;
        ( *root )->left = NULL;
        ( *root )->right = NULL;
    } else {
        rand() > RAND_MAX / 2 ? FillTreeRandomly( &( *root )->left ) : FillTreeRandomly( &( *root )->right );
    }
}