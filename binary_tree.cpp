#include <iostream>
#include <cstdlib>

using namespace std;

#define N 100
#define R 2

typedef struct BSTNode {
	int value;
	struct BSTNode *left;
	struct BSTNode *right;
}BSTNode;

BSTNode *constructBST(int *hay, int low, int high);
void freeBSTNodes(BSTNode *node);
void printBSTInorder(BSTNode *node);
bool binaryTreeSearch(BSTNode *tree, int needle);

int main() {
	int hay[N];
	int thres = RAND_MAX / R;

	/* Creates a sorted array with gaps between elements depending on R */
	for (int i=0, val = 0; i < N; val++) {
		(rand() > thres) ? hay[i++] = val : val++;
	}

	BSTNode *root = constructBST(hay, 0,N-1);
	printBSTInorder(root);
	for (int i=0; i<N; i++) {
		cout << i << " is " << (binaryTreeSearch(root,i) ? "" : " not ") << "present" << endl;
	}

	freeBSTNodes(root);
}

BSTNode *constructBST(int *hay, int low, int high) {
	if (low <= high) {
		int mid = (low + high) / 2;
		BSTNode *node = new BSTNode();

		node->value = hay[mid];
		node->left = constructBST(hay, low, mid-1);
		node->right = constructBST(hay, mid+1, high);

		return node;
	}
	return NULL;
}

void freeBSTNodes(BSTNode *node) {
	if (node == NULL) return;

	freeBSTNodes(node->left);
	freeBSTNodes(node->right);
	delete(node);
}

void printBSTInorder(BSTNode *node) {
	if (node == NULL) return;
	printBSTInorder(node->left);
	cout << node->value << endl;
	printBSTInorder(node->right);
}

bool binaryTreeSearch(BSTNode *tree, int needle) {
	if (tree == NULL) return false;
	if (needle == tree->value) return true;
	if (needle < tree->value) 
		return binaryTreeSearch(tree->left, needle);
	else 
		return binaryTreeSearch(tree->right, needle);
}
