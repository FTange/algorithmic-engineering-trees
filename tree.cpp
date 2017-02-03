#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// #define N 15
int N = 15;
int H = 4; // log2(N)
#define R 1.5

/*
 * Double 0 <= skew <= 1 is the proportion of the tree put in left subtree
 * Not filled from left to right, middle should start with largest power of 2
 * smaller than or equal to N/2
 */

ofstream myfile;

void constructSkewedBFS(int *arr, double skew, int pos, int low, int high) {
	if (low <= high) {
		int mid = (low + high) * skew;

		myfile << "    tree[" << pos << "] = " << arr[mid] << ";" << endl;
		constructSkewedBFS(arr, skew, 2*pos, low, mid-1);
		constructSkewedBFS(arr, skew, 2*pos+1, mid+1, high);
	}
}

void constructSkewedBFS(int *arr, double skew) {
	constructSkewedBFS(arr, skew, 1,0,N-1);
}

// start with mid being the highest power of 2 larger than N/2
// works with N being a power of 2 -1
int constructSkewedDFS(int *arr, double skew, int pos, int low, int high) {
	if (low <= high) {
		int mid = (low + high) * skew;

		myfile << "    tree[" << pos << "] = " << arr[mid] << ";" << endl;
		int sizeLeftTree  = constructSkewedDFS(arr, skew, pos+1, low, mid-1);
		int sizeRightTree = constructSkewedDFS(arr, skew, pos+sizeLeftTree+1, mid+1, high);
		return sizeLeftTree + sizeRightTree + 1;
	}
	return 0;
}

void constructSkewedDFS(int *arr, double skew) {
	constructSkewedDFS(arr, skew, 0,0,N-1);
}

int main(int argc, char* argv[]) {
	bool bfs = true;
	// strcmp is 0 when they are equal
	if (argc == 3 && !strcmp(argv[2], "dfs")) {
		bfs = false;
	}
	if (argc > 1) {
		H = atoi(argv[1]);
		N = (1 << H) - 1;
	}
	cout << N << endl;
	int hay[N];
	int thres = RAND_MAX / R;

	/* Creates a sorted array with gaps between elements depending on R */
	for (int i=0, val = 0; i < N; val++) {
		//(rand() < thres) ? hay[i++] = val : val++;
		hay[i] = i;
		i++;
	}

	myfile.open("tree.txt");
	myfile << "int tree[" << N+1 << "];" << endl;
	myfile << "int N = " << N << ";" << endl;
	myfile << "int H = " << H << ";" << endl;
	myfile << "bool bfs = " << bfs << ";" << endl;
	myfile << "int initialize() {" << endl;
	if (bfs) {
		constructSkewedBFS(hay, 0.5);
	} else {
		constructSkewedDFS(hay, 0.5);
	}
	myfile << "    return " << N << ";" << endl;
	myfile << "}" << endl;
	myfile.close();
}
