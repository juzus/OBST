// OBST.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include "OptimalBST.h"
using namespace std;

int main()
{
	std::string fileName;
	std::string fileContents;
	int count = 0;
	OptimalBST obst;
	//NOTE: filename doesn't currently have its file type appended to it. might change
	cout << "Enter the filename for the frequency input you would like to use.\nNote that the file should be located in the program directory ==> ";
	cin >> fileName;
	std::ifstream file;
	file.open(fileName);
	file.seekg(0, file.end);
	fileContents.reserve(file.tellg());
	file.seekg(0, file.beg);
	fileContents.assign((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	file.close();
	cout << fileContents << endl;
	// remove commas from file data string
	fileContents.erase(std::remove(fileContents.begin(), fileContents.end(), ','), fileContents.end());
	//count = countZeroes(fileContents);
	//cout << count;
	// Store tree frequencies in vector
	std::stringstream ss(fileContents);
	vector<int> freq;
	int num;
	while (ss >> num) {
	freq.push_back(num);
	}
	if (freq.back() == 0) {
		freq.pop_back();
	}
	//insert 0 at beginning of frequency vector to account for initial values for sub-trees
	// freq.insert(freq.begin(), 0);
	obst.setFrequencies(freq);
	obst.optimizeBST();
	cout << "\nPress any key to end this program.";
	if (cin >> fileName)
		exit(0);
}
