#include <iostream>
#include <cstdlib>
#include <stack>
#include "tree.txt"

using namespace std;

// tree contains N-1 values
#define R 1.5

void constructSkewedBFS(int *arr, int *tree, double skew);
void constructSkewedBFS(int *arr, int *tree, double skew, int pos, int low, int high);
void printBFSInorder(int *tree);
void printBFSInorder(int *tree, int pos);
bool binaryBFSSearch(int *tree, int needle);
int  getBFSPred(int *tree, int needle);

void constructSkewedDFS(int *arr, int *tree, double skew);
int  constructSkewedDFS(int *arr, int *tree, double skew, int pos, int low, int high);
void printDFSInorder(int *tree);
void printDFSInorder(int *tree, int pos, int level);
bool binaryDFSSearch(int *tree, int needle, int level);
int  getDFSPred(int *tree, int needle, int level);

int main(int argc, char *argv[]) {
	N = initialize();
	if (bfs) {
		printBFSInorder(tree);
	} else {
		printDFSInorder(tree);
	}
	cout << "N is " << N << " H is " << H << endl;

	/*
	for (int i=0; i<N; i++) {
		//cout << tree[i] << " has position " << i << endl;
		cout  << "pred of " << i << " is " << getBFSPred(tree, i) << ", " << i << " is " 
			<< ((binaryBFSSearch(tree, i)) ? "" : "not ") << "present in tree" << endl;
	}
	*/
}

/*
 * TODO - make function to either save array or c++ instruction to construct array to
 *		  a file instead of constructing it at runtime
 *		  https://stackoverflow.com/questions/410980/include-a-text-file-in-a-c-program-as-a-char
 *		  https://stackoverflow.com/questions/11409021/c-program-sees-an-included-txt-file-as-code
 */
void constructSkewedBFS(int *arr, int *tree, double skew) {
	constructSkewedBFS(arr, tree, skew, 1,0,N-1);
}

/*
 * Double 0 <= skew <= 1 is the proportion of the tree put in left subtree
 * Not filled from left to right, middle should start with largest power of 2
 * smaller than or equal to N/2
 */
void constructSkewedBFS(int *arr, int *tree, double skew, int pos, int low, int high) {
	if (low <= high) {
		int mid = (low + high) * skew;

		tree[pos] = arr[mid];
		constructSkewedBFS(arr, tree, skew, 2*pos, low, mid-1);
		constructSkewedBFS(arr, tree, skew, 2*pos+1, mid+1, high);
	}
}

void printBFSInorder(int *tree) {
	printBFSInorder(tree, 1);
}

void printBFSInorder(int *tree, int pos) {
	if (pos <= N) {
		printBFSInorder(tree, 2*pos);
		cout << tree[pos] << " has position " << pos << endl;
		printBFSInorder(tree, 2*pos+1);
	}
}

bool binaryBFSSearch(int *tree, int needle) {
	int pos = 1;
	while (pos < N) {
		if (tree[pos] == needle) return true;
		int left = 2*pos, right = 2*pos+1;
		pos = left ^ ((right ^ left) & -(needle > tree[pos]));
	}
	return false;
}

int getBFSPred(int *tree, int needle) {
	int pos = 1, possPred = -1;
	while (pos < N) {
		int currVal = tree[pos];
		if (currVal == needle) {
			// no left subtree
			if (pos*2 >= N) break;
			pos = pos*2;
			// find largest elem in left subtree
			while (pos*2+1 < N) { 
				pos = pos*2+1;
			}
			return tree[pos];
		}
		// save tree[pos] as possible pred if it is greater than previous parent and smaller than needle
		possPred = possPred ^ ((currVal ^ possPred) & -((possPred < currVal) & (currVal < needle)));
		// pos = (needle < tree[pos]) ? 2*pos : 2*pos+1;
		int left = 2*pos, right = 2*pos+1;
		pos = left ^ ((right ^ left) & -(needle > currVal));
	}
	return possPred;
}

// DFS functions

void constructSkewedDFS(int *arr, int *tree, double skew) {
	constructSkewedDFS(arr, tree, skew, 0,0,N-1);
}

// start with mid being the highest power of 2 larger than N/2
// works with N being a power of 2 -1
int constructSkewedDFS(int *arr, int *tree, double skew, int pos, int low, int high) {
	if (low <= high) {
		int mid = (low + high) * skew;

		tree[pos] = arr[mid];
		int sizeLeftTree  = constructSkewedDFS(arr, tree, skew, pos+1, low, mid-1);
		int sizeRightTree = constructSkewedDFS(arr, tree, skew, pos+sizeLeftTree+1, mid+1, high);
		return sizeLeftTree + sizeRightTree + 1;
	}
	return 0;
}

void printDFSInorder(int *tree) {
	printDFSInorder(tree, 0, H);
}

void printDFSInorder(int *tree, int pos, int level) {
	if (level > 0) {
		printDFSInorder(tree, pos+1, level - 1);
		cout << tree[pos] << " has position " << pos << endl;
		printDFSInorder(tree, pos+ (1 << (level-1)), level - 1);
	}
}

bool binaryDFSSearch(int *tree, int needle, int level) {
	int pos = 0;
	while (level > 0) {
		if (tree[pos] == needle) return true;
		int left = pos+1, right = pos + (1 << (level-1));
		pos = left ^ ((right ^ left) & -(needle < tree[pos]));
	}
	return false;
}

int getDFSPred(int *tree, int needle, int level) {
	int pos = 0, possPred = -1;
	while (level > 0) {
		int currVal = tree[pos];
		if (currVal == needle) {
			// no left subtree
			if ((level -= 1) == 0) { break; }
			pos = pos+1;
			// when one we are at leaf nodes
			while (level > 1) { 
				pos += (1 << (level-1));
				level--;
			}
			return tree[pos];
		}
		// save tree[pos] as possible pred if it is greater than previous parent and smaller than needle
		possPred = possPred ^ ((currVal ^ possPred) & -((possPred < currVal) & (currVal < needle)));
		// pos = (needle < tree[pos]) ? 2*pos : 2*pos+1;
		int left = pos+1, right = pos+(1 << (level-1));
		pos = left ^ ((right ^ left) & -(needle > tree[pos]));
		level--;
	}
	return possPred;
}
