#include <iostream>
#include <cstdlib>
#include <stack>

using namespace std;

// tree contains N-1 values
#define N 16
#define R 1.5

void constructSkewedBFS(int *arr, int *tree, double skew);
void constructSkewedBFS(int *arr, int *tree, double skew, int pos, int low, int high);
void printBFSInorder(int *tree);
void printBFSInorder(int *tree, int pos);
bool binaryBFSSearch(int *tree, int needle);
int  getBFSPred(int *tree, int needle);

void constructSkewedDFS(int *arr, int *tree, double skew);
void constructSkewedDFS(int *arr, int *tree, double skew, int pos, int low, int high);
void printDFSInorder(int *tree);
void printDFSInorder(int *tree, int pos);
bool binaryDFSSearch(int *tree, int needle);
int  getDFSPred(int *tree, int needle);

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

	constructSkewedBFS(hay, tree, 0.5);

	// printBFSInorder(tree);

	/*
	for (int i=0; i<N; i++) {
		cout << i << " is " << (binaryBFSSearch(root,i) ? "" : " not ") << "present" << endl;
	}
	*/
	for (int i=0; i<hay[N-1]; i++) {
		//cout << tree[i] << " has position " << i << endl;
		cout << "pred of " << i << " is " << getBFSPred(tree, i) << ", " << i << " is " 
			<< ((binaryBFSSearch(tree, i)) ? "" : "not ") << "present in tree" << endl;
	}
}

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
	if (pos < N) {
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
	// TODO
}

void constructSkewedDFS(int *arr, int *tree, double skew, int pos, int low, int high) {
	// TODO
}

void printDFSInorder(int *tree) {
	// TODO
}

void printDFSInorder(int *tree, int pos) {
	// TODO
}

bool binaryDFSSearch(int *tree, int needle) {
	// TODO
	return false;
}

int getDFSPred(int *tree, int needle) {
	// TODO
	return 0;
}
