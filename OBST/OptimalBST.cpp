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
}

void OptimalBST::determineLength() {
	length = freqInput.size();
}

void OptimalBST::initialize() {
	determineLength();
	weights.resize(length);
	complexities.resize(length);
	//first populate the initial frequency and complexity values for row 1/column 1, row 2/column 2, etc.
	for (int h = 0; h < length; h++) {
		weights[h].resize(length);
		weights[h][h] = freqInput[h];
		complexities[h].resize(length);
		complexities[h][h] = freqInput[h];
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