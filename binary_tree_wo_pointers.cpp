#include <iostream>
#include <cstdlib>
#include <stack>

using namespace std;

// tree contains N-1 values
#define N 16
#define R 1.5

void printBSTInorder(int *tree);
void printBSTInorder(int *tree, int pos);
bool binaryTreeSearch(int *tree, int needle);
void constructSkewedBST(int *arr, int *tree, double skew);
void constructSkewedBST(int *arr, int *tree, double skew, int pos, int low, int high);
int getPred(int *tree, int needle);

int main() {
	// tree array begins at position 1 for simplicity
	int hay[N], tree[N+1];
	int thres = RAND_MAX / R;

	/* Creates a sorted array with gaps between elements depending on R */
	for (int i=0, val = 0; i < N; val++) {
		(rand() < thres) ? hay[i++] = val : val++;
		// hay[i] = i;
		// i++;
	}

	constructSkewedBST(hay, tree, 0.5);

	// printBSTInorder(tree);

	/*
	for (int i=0; i<N; i++) {
		cout << i << " is " << (binaryTreeSearch(root,i) ? "" : " not ") << "present" << endl;
	}
	*/
	for (int i=0; i<hay[N-1]; i++) {
		//cout << tree[i] << " has position " << i << endl;
		cout << "pred of " << i << " is " << getPred(tree, i) << ", " << i << " is " 
			<< ((binaryTreeSearch(tree, i)) ? "" : "not ") << "present in tree" << endl;
	}
}

void constructSkewedBST(int *arr, int *tree, double skew) {
	constructSkewedBST(arr, tree, skew, 1,0,N-1);
}

/*
 * Double 0 <= skew <= 1 is the proportion of the tree put in left subtree
 */
void constructSkewedBST(int *arr, int *tree, double skew, int pos, int low, int high) {
	if (low <= high) {
		int mid = (low + high) * skew;

		tree[pos] = arr[mid];
		constructSkewedBST(arr, tree, skew, 2*pos, low, mid-1);
		constructSkewedBST(arr, tree, skew, 2*pos+1, mid+1, high);
	}
}

void printBSTInorder(int *tree) {
	printBSTInorder(tree, 1);
}

void printBSTInorder(int *tree, int pos) {
	if (pos < N) {
		printBSTInorder(tree, 2*pos);
		cout << tree[pos] << " has position " << pos << endl;
		printBSTInorder(tree, 2*pos+1);
	}
}

bool binaryTreeSearch(int *tree, int needle) {
	int pos = 1;
	while (pos < N) {
		if (tree[pos] == needle) return true;
		int left = 2*pos, right = 2*pos+1;
		pos = left ^ ((right ^ left) & -(needle > tree[pos]));
	}
	return false;
}

// Optimize to not use stack
int getPred(int *tree, int needle) {
	int pos = 1;
	stack<int> visitedVals;
	while (pos < N) {
		if (tree[pos] == needle) {
			// no left subtree
			if (pos*2 >= N) break;
			pos = pos*2;
			// find largest elem in left subtree
			while (pos*2+1 < N) { 
				pos = pos*2+1;
			}
			return tree[pos];

		}
		visitedVals.push(tree[pos]);
		// pos = (needle < tree[pos]) ? 2*pos : 2*pos+1;
		int left = 2*pos, right = 2*pos+1;
		pos = left ^ ((right ^ left) & -(needle > tree[pos]));
	}
	while (!visitedVals.empty()) {
		int val = visitedVals.top();
		// stupid c++
		visitedVals.pop();
		if (val < needle) {
			return val;
		}
	}
	return -1;
}
