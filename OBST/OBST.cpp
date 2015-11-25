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
#include <tchar.h>
#include <Windows.h>
#include "OptimalBST.h"
using namespace std;

LARGE_INTEGER frequency; //ticks per second
LARGE_INTEGER t1, t2; //ticks
double elapsedTime;

int main()
{
	std::string fileName;
	std::string fileContents;
	int count = 0;
	OptimalBST obst;
	bool in = false;
	bool cont = true;

	while (cont == true) {
		in = false;
		cout << "Enter the filename for the frequency input you would like to use.\
				\nNote that the file should be located in the program directory, and only DAT files are valid.\
				\nDO NOT INCLUDE THE EXTENSION, since we will presume it is a DAT file ==> ";
		
		cin >> fileName;
		std::ifstream file;
		file.open(fileName+".dat");
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
		// Call timers
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&t1);
		obst.optimizeBST();
		// Stop timers.
		QueryPerformanceCounter(&t2);
		int elapsedTime = (t2.QuadPart - t1.QuadPart)* 1000.0 / frequency.QuadPart;
		cout << "Time elapsed for the optimize, tree construction and traversal algorithms: " << elapsedTime << "ms" << endl;
		cout << "\nWould you like to read in another input file? (y/n): ";
		string answer;
		while (in == false) {
			cin >> answer;
			if (answer == "y" || answer == "Y") {
				in = true;
				obst.cleanup();
			}
			else if (answer == "n" || answer == "N") {
				in = true;
				cont = false;
			}
			else {
				cout << endl << "Invalid input. Please try again." << endl;
			}
		}
	}
	exit(0);
}
