#include <iostream>
#include <cstdlib>

using namespace std;

bool binarySearch(int *hay, int needle);

#define N 100
#define R 2

int main() {
	int hay[N];
	int thres = RAND_MAX / R;

	/* Creates a sorted array with gaps between elements depending on R */
	for (int i=0, val = 0; i < N; val++) {
		(rand() > thres) ? hay[i++] = val : val++;
	}

	/*int needle = 101;
	cout << (binarySearch(hay, needle) ? "Found it" : "Not found") << endl; */

	int found = 0, notFound = 0;
	for (int i=0; i < hay[N-1]; i++) {
		(binarySearch(hay, i)) ? found++: notFound++;
	}

	cout << found << " numbers was found, " << notFound << " numbers was not found" << endl;

	/*
	for (int i=0; i<N; i++) {
		printf("%d\n", hay[i]);
	}
	*/
}

bool binarySearch(int *hay, int needle) {
	int low = 0, high = N-1, mid;
	while (low <= high) {
		mid = (high + low) / 2;
		int straw = hay[mid];
		if (straw == needle) return true;
		(straw < needle) ? low = mid+1 : high = mid-1;
	}
	return false;

}