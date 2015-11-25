#include "stdafx.h"
#include "OptimalBST.h"

using namespace std;

OptimalBST::OptimalBST() : root(NULL) {}


OptimalBST::~OptimalBST() {
}

void OptimalBST::setFrequencies(std::vector<int> f) {
	freqInput = f;
}

// Algorithm O(n^3), meaning that we will iterate through key ranges and determine weights/complexity/roots at each unique range
void OptimalBST::optimizeBST() {
	initialize();
	cout << "\nNumber of keys in tree: " << length << endl;
	sumFrequencies();
	int i, j, r;
	
	// Calculate the average time complexity for each sub-tree and for the resulting tree.
	// i = row; j = column; numKeys = number of keys in the sub-tree.
	// the outer loop is based on numKeys because we want to start from the inital sub-tree up to the resulting tree.
	// We already populated the weights for all key ranges into a 2D matrix.
	// We also already initialized the complexities for individual keys and populated those initial values
	// into the complexities 2D matrix, so that complexities[1][1] doesn't need to be populated, for instance.
	// This is why numKeys is initialized to 2 instead of 1 in the outer loop.

	// Calculate roots in the same loop. Store root for each sub-tree, plus either the 2nd-most-optimal root,
	// or the roots that have equivalent complexity to the chosen root.
	for (int numKeys = 2; numKeys <= length; numKeys++) {
		for (i = 0; i <= length - numKeys; i++) {
			int j = i + numKeys - 1;
			findRoots(i, j);
		}
	}

	// Construct optimal BST
	root = constructTree(0, length - 1, 1);

	// Get optimal BST's standard deviation
	calcStdDev();
	
	//outputResults();
	cout << "\n>>> For a Find Operation on the Optimal BST:\
			\nStandard Deviation = " << std_dev << 
		    "\nBest and Worst Case: O(" << length << "^3)" << endl;
	
	// output breadth-first traversal for first 3 levels of tree
	levelOrderTraversal(root);
	
	// clear tree before constructing second tree
	deleteTree(root);
	
	// second tree's root is indicated
	rootIndex = 1;	
	
	// do all of the same as above for the second tree
	root = constructTree(0, length - 1, 1);
	
	calcStdDev();
	
	if (rcs[0][length-1][0].complexity == rcs[0][length-1][1].complexity) {
		cout << "\n>>> For a Find Operation on the Alternative Optimal BST With Equal Complexity:\
				\nStandard Deviation = " << std_dev << endl;
	}
	else {
		cout << "\n>>> For a Find Operation on the Second Most Optimal BST:\
				\nStandard Deviation: " << std_dev << endl;
	}
	cout << "Best and Worst Case = " << "O(" << length << "^3)" << endl;
	levelOrderTraversal(root);
	deleteTree(root);
}

void OptimalBST::findRoots(int i, int j) {
	int weight = weights[i][j];
	int c=0; // temp storage for complexity values
	bool hasMatchingComplexity;

	for (int k = i; k <= j; k++) {

		// sum the total complexity for the kth root
		if (k > i) {
			c += rcs[i][k - 1][0].complexity;
		}
		if (k < j) {
			c += rcs[k + 1][j][0].complexity;
		}

		// add complexities/roots in 3D vectors
		rcs[i][j].emplace_back(rc{ (c + weight), k });
		c = 0;
	}
	// sorts the roots in ascending order, so whether there are matching optimal values or not, 
	// it will be sorted so the 0th and 1st value will store the optimal and alternative trees
	// the root at index 0 is the optimal root, the root at index 1 is either the second most optimal
	// root or the alternative optimal root
	sort(rcs[i][j].begin(), rcs[i][j].end(),
		[&](rc a, rc b) {
		return (a.complexity < b.complexity);
	});
}

void OptimalBST::determineLength() {
	length = freqInput.size();
}

void OptimalBST::initialize() {
	determineLength();
	weights.resize(length);
	rcs.resize(length);

	//first populate the initial frequency, complexity, and root values for row 1/column 1, row 2/column 2, etc.
	for (int h = 0; h < length; h++) {
		weights[h].resize(length);
		weights[h][h] = freqInput[h];
		rcs[h].resize(length);
		rcs[h][h].emplace_back(rc{ freqInput[h], h });
		rcs[h][h].emplace_back(rc{ freqInput[h], h });
	}
}

void OptimalBST::sumFrequencies() {
	int i, j, k, sum = 0;

	// numKeys is the number of keys in the sub-tree. We have to work from the bottom up.
	for (int numKeys = 2; numKeys <= length; numKeys++) {
		
		// i = row; end condition is based on the numKeys because we don't need 
		// to access every row depending on the amount in numKeys
		for (i = 0; i <= length - numKeys; i++) {
			
			// j = column, and value depends on the row and the number of keys
			// for this sub-tree
			j = i + numKeys - 1;
			
			for (k = i; k <= j; k++) {
				sum += freqInput[k];
			}
			weights[i][j] = sum;
			sum = 0;
		}
	}
}

OptimalBST::node* OptimalBST::constructTree(int begin, int end, int level) {
	// standard linked-list-style binary search tree that I implemented with
	// a struct called node
	node* n;

	// Tree only needs to be constructed to the 3rd level
	if (level == 4) {
		return NULL;
	}
	else {
		int r = rcs[begin][end][rootIndex].root;
		n = new node();
		n->key = r;
		n->level = level;
		
		// a way to keep track of the level of the leaves in a constructed tree.
		rcs[r][r][rootIndex].level = level;
		
		if (begin == end) {
			return n;
		}
		else {
			n->left = constructTree(begin, r - 1, level + 1);
			n->right = constructTree(r + 1, end, level + 1);
		}
	}
	return n;
}

void OptimalBST::deleteTree(node* r) {
	// free up memory after tree is no longer needed

	if (r != NULL) {
		deleteTree(r->left);
		deleteTree(r->right);
	}
	delete r;
}

void OptimalBST::levelOrderTraversal(node* root) {
	//if (level == 4) {
	//	//int pr = weights[begin][end] / sumWeights;
	//	//mean[r] = (pr * level);
	//	//variance[r] = (level * level) * pr;
	//	return;
	//}

	//cout << "level: " << level << ", " << r;
	//if (begin == end){
	//	return;
	//}
	//else {
	//	if ( nodeCount == pow(2,level) ) {
	//		level++; //increment level when the nodes for current level have reached 2^n i.e. the max # of nodes for that level
	//	}
	//	levelOrderTraversal(begin, r - 1, rcs[begin][r-1][0].root, level);
	//	levelOrderTraversal(r + 1, end, rcs[r + 1][end][0].root, level);
	//}
	// BFS tree traversal using a queue treeQ, r for the root/key value to be pushed to the queue for output,
	// and begin/end values to keep track of subtrees, and level to keep track of the tree's level and stop at level 3
	
	//Uses a queue to perform breadth-first traversal.

	cout << "\nLevel Order Traversal:\n";
	queue<node*> treeQ;
	if (root) {
		treeQ.push(root);
	}

	while (!treeQ.empty()) {
		const node* const temp = treeQ.front();
		treeQ.pop();
		cout << "level: " << temp->level << ", value: " << temp->key << endl;
		
		if (temp->left) {
			treeQ.push(temp->left);
		}
		if (temp->right) {
			treeQ.push(temp->right);
		}
	}
}

void OptimalBST::calcStdDev() {
	
	//initialize values to determine std. deviation
	sumWeights = weights[0][length - 1];
	m.resize(length);
	v.resize(length);
	rootIndex = 0;
	mean = 0;
	variance = 0;
	std_dev = 0;

	// Each leaf node's auxiliary values are stored in the m vector for the mean
	// or the v vector for the variance.
	for (int i = 0; i < length; i++) {
		rc k = rcs[i][i][rootIndex];
		float lvl = k.level;
		float wgt = k.complexity;
		float pr = wgt / sumWeights;
		m.push_back(lvl*pr);
		v.push_back((lvl*lvl) * pr);

		mean += (lvl * pr);
		variance += ( (lvl * lvl) * pr );
	}
	float difference = variance - (mean * mean);
	std_dev = sqrt(difference);
}

void OptimalBST::cleanup() {
	// Free up memory for this instance before another input file is read in.

	rcs.clear();
	weights.clear();
	freqInput.clear();
	m.clear();
	v.clear();
	mean = 0;
	variance = 0;
	std_dev = 0;
	length = 0;
	sumWeights = 0;
	rootIndex = 0;
}