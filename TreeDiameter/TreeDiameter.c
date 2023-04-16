#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

int diameterOfBinaryTree(struct TreeNode* root);
int FindDown_r( struct TreeNode* branch );
void FillTreeRandomly_r( struct TreeNode** root );

int  maximum = 0;

int main() {
	struct TreeNode* root = NULL;

	srand( time( NULL ) );

	for( int i = 0; i < 100; i++ ) {
		FillTreeRandomly_r( &root );
	}

	printf( "%d\n", diameterOfBinaryTree( root ) );

	return 0;
}

int diameterOfBinaryTree(struct TreeNode* root){
	FindDown_r( root );

	return maximum;
}

int FindDown_r( struct TreeNode* branch ) {
	int  left;
	int  right;

	if ( branch->left != NULL ) {
		left = FindDown_r( branch->left );
	} else {
		left = 0;
	}

	if ( branch->right != NULL ) {
		right = FindDown_r( branch->right );
	} else {
		right = 0;
	}

	if ( left + right > maximum ) {
		maximum = left + right;
	}
	
	return 1 + ( left > right ? left : right );
}

void FillTreeRandomly_r( struct TreeNode** root ) {
	if ( *root == NULL ) {
		*root = malloc( sizeof( struct TreeNode ) );

		( *root )->val = rand() % 201 - 100;
		( *root )->left = NULL;
		( *root )->right = NULL;
	} else {
		rand() > RAND_MAX / 2 ? FillTreeRandomly_r( &( *root )->left ) : FillTreeRandomly_r( &( *root )->right );
	}
}