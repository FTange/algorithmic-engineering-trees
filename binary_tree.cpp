#include <iostream>
#include <cstdlib>

using namespace std;

#define N 100
#define R 1.5

typedef struct BSTNode {
	int value;
	struct BSTNode *left;
	struct BSTNode *right;
}BSTNode;

BSTNode *constructBST(int *hay, int low, int high);
BSTNode *constructSkewedBST(int *hay, double skew, int low, int high);
BSTNode *constructBST(int *hay);
BSTNode *largestSubTreeNode(BSTNode *node);
BSTNode *getPred(BSTNode *tree, int needle);
void freeBSTNodes(BSTNode *node);
void printBSTInorder(BSTNode *node);
bool binaryTreeSearch(BSTNode *tree, int needle);
int treeSize(BSTNode *node);

int main() {
	int hay[N];
	int thres = RAND_MAX / R;

	/* Creates a sorted array with gaps between elements depending on R */
	for (int i=0, val = 0; i < N; val++) {
		(rand() < thres) ? hay[i++] = val : val++;
	}

	BSTNode *root = constructSkewedBST(hay, 0.5, 0,N-1);

	printBSTInorder(root);

	/*
	for (int i=0; i<N; i++) {
		cout << i << " is " << (binaryTreeSearch(root,i) ? "" : " not ") << "present" << endl;
	}
	*/

	BSTNode *pred = getPred(root, 30);
	cout << "pred is " << pred->value << endl;

	freeBSTNodes(root);
}

BSTNode *constructBST(int *hay) {
	return constructBST(hay, 0, N);
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

/*
 * Double 0 <= skew <= 1 is the proportion of the tree put in left subtree
 */
BSTNode *constructSkewedBST(int *hay, double skew, int low, int high) {
	if (low <= high) {
		int mid = (low + high) * skew;
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

int treeSize(BSTNode *node) {
	if (node == NULL) return 0;
	int size = 1 + treeSize(node->left) + treeSize(node->right);
	return size;
}

/*
 * We did find the needle:
	* Rightmost leaf in left subtree is pred
	* If no left subtree, pred is the first parent smaller than needle
 * We didn't find the needle:
	* No left subtree, first parent smaller than needle is pred
 */
BSTNode *getPred(BSTNode *tree, int needle) {
	if (tree == NULL)
		return NULL;
	if (needle == tree->value)
		// return largest elem in left subtree
		return largestSubTreeNode(tree->left);
	BSTNode *pred;
	if (needle < tree->value)
		pred = getPred(tree->left, needle);
	else
		pred = getPred(tree->right, needle);
	// return pred if found, if not and parent is smaller than needle, parent is pred
	pred = ((pred != NULL) ? pred : ((tree->value < needle) ? tree : NULL));
	return pred;
}

BSTNode *largestSubTreeNode(BSTNode *node) {
	if (node == NULL) return NULL;
	while (node->right != NULL) {
		node = node->right;
	}
	return node;
}
