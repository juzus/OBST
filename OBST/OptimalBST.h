#include <queue>
#pragma once

class OptimalBST
{	
	struct rc {
		int complexity;
		int root;
		int level;
	};

	struct node {
		int key;
		int level;
		node* left;
		node* right;
	};
	node* root;

	std::vector<int> freqInput;
	std::vector< std::vector<int> > weights;
	std::vector< std::vector< std::vector<rc> > > rcs;
	//vector of integer vectors, storing  1st and 2nd roots
	// vector of integer vectors storing information for each sub-tree. 
										   // index 0: sub-tree key range
										   // index 1: sub-tree weight
										   // index 2: sub-tree average time complexity
										   // index 3: sub-tree root
	std::vector<double> m;
	std::vector<double> v;
	float mean;
	float variance;
	float std_dev;
	int length;
	float sumWeights;
	int rootIndex;


	public:
	
	OptimalBST();
	~OptimalBST();
	void setFrequencies(std::vector<int> f);
	void optimizeBST();
	void determineLength();
	void initialize();
	void sumFrequencies();
	void findRoots(int i, int j);
	node* constructTree(int begin, int end, int level);
	void levelOrderTraversal(node* root);
	void calcStdDev();
	void deleteTree(node* r);
	void cleanup();
	//void outputResults();
};

