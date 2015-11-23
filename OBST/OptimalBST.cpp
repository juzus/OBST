#include "stdafx.h"
#include "OptimalBST.h"

using namespace std;

OptimalBST::OptimalBST() {}


OptimalBST::~OptimalBST() {
	//TODO: Write destructor to free up memory
}

void OptimalBST::setFrequencies(std::vector<int> f) {
	freqInput = f;
}

// Algorithm O(n^3), meaning that we will iterate through key ranges and determine weights/complexity/roots at each unique range
void OptimalBST::optimizeBST() {
	initialize();
	sumFrequencies();
	int i, j, r;
	// Calculate the average time complexity for each sub-tree and for the resulting tree.
	// i = row; j = column; numKeys = number of keys in the sub-tree.
	// the outer loop is based on numKeys because we want to start from the inital sub-tree up to the resulting tree.
	// We already populated the weights for all key ranges into a 2D matrix.
	// We also already initialized the complexities for individual keys and populated those initial values
	//     into the complexities 2D matrix, so that complexities[1][1] doesn't need to be populated, for instance.
	//     This is why numKeys is initialized to 2 instead of 1 in the outer loop.

	// Calculate roots in the same loop. Store root for each sub-tree, plus either the 2nd-most-optimal root,
	// or the roots that have equivalent complexity to the chosen root.
	for (int numKeys = 2; numKeys <= length; numKeys++) {
		for (i = 0; i < length - numKeys; i++) {
			int j = i + numKeys - 1;
			findRoots(i, j);
		}
	}
}

void OptimalBST::findRoots(int i, int j) {
	int weight = weights[i][j];
	int c=0;
	bool hasMatchingComplexity;
	for (int k = i; k <= j; k++) {
		// sum the total complexity for the kth root
		if (k > i) {
			//c += complexities[i][k - 1][0];
			c += rcs[i][k - 1][0]->complexity;
		}
		if (k < j) {
			//c += complexities[k + 1][j][0];
			c += rcs[k + 1][j][0]->complexity;
		}

		// add complexities/roots in 3D vectors
		complexities[i][j].push_back(c);
		roots[i][j].push_back(k);
		rc* myRC = new rc();
		myRC->complexity = c;
		myRC->root = k;
		rcs[i][j].push_back(myRC);
		c = 0;
	}
	// sorts the roots in ascending order, so whether there are matching optimal values or not, 
	// it will be sorted so the 0th and 1st value will store the optimal and alternative trees
	sort(rcs[i][j].begin(), rcs[i][j].end(),
		[&](rc* a, rc* b) {
		return (a->complexity < b->complexity);
	});
}

void OptimalBST::determineLength() {
	length = freqInput.size();
}

void OptimalBST::initialize() {
	determineLength();
	weights.resize(length);
	complexities.resize(length);
	roots.resize(length);
	rcs.resize(length);
	//first populate the initial frequency, complexity, and root values for row 1/column 1, row 2/column 2, etc.
	for (int h = 0; h < length; h++) {
		rc* myRC = new rc();
		weights[h].resize(length);
		weights[h][h] = freqInput[h];
		complexities[h].resize(length);
		complexities[h][h].push_back(freqInput[h]);
		roots[h].resize(length);
		roots[h][h].push_back(h);
		rcs[h].resize(length);
		myRC->complexity = freqInput[h];
		myRC->root = h;
		rcs[h][h].push_back(myRC);
	}
}

void OptimalBST::sumFrequencies() {
	// thought i could iterate through more straightforwardly, then realized that I needed to build up from the bottom of each column.
	// so, had to iterate through based on number of keys in the sub-tree 
	int i, j, k, sum = 0;

	// numKeys is the number of keys in the sub-tree. We have to work from the bottom up.
	for (int numKeys = 2; numKeys <= length; numKeys++) {
		// i = row; end condition is based on the numKeys because we don't need 
		// to access every row depending on the amount in numKeys
		for (i = 0; i <= length - numKeys; i++) {
			j = i + numKeys - 1;
			for (k = i; k <= j; k++) {
				sum += freqInput[k];
			}
			weights[i][j] = sum;
			sum = 0;
		}
	}
	/*Original way of iterating below. Write about how you tried this and learned by doing it on paper that this wouldn't work*/
	//for (i; i < length; i++) {
	//	for (j=i; j < length; i++) {
	//		int sum = 0;
	//		// might want to take this conditional out of the loop and just set the initial frequencies separately
	//		if (i == j) {
	//			frequencies[i][j] = freqInput[i];
	//		}
	//		else {
	//			for (int k = i; k <= j; k++) {
	//				sum += freque
	//			}
	//		}
	//	}
	//}
}