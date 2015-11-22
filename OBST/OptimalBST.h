#include <vector>
#include <string>

#pragma once

class OptimalBST
{
	std::vector<int> freqInput;
	std::vector< std::vector<int> > weights;
	std::vector< std::vector<int> > complexities;
	std::vector< std::vector<int> > roots; //vector of integer vectors, storing  1st and 2nd roots
	std::vector< std::vector<std::string> > chart; // vector of integer vectors storing information for each sub-tree. 
										   // index 0: sub-tree key range
										   // index 1: sub-tree weight
										   // index 2: sub-tree average time complexity
										   // index 3: sub-tree root
	int length;

	public:
	
	OptimalBST();
	~OptimalBST();
	void setFrequencies(std::vector<int> f);
	void optimizeBST();
	void determineLength();
	void initialize();
	void sumFrequencies();
};

