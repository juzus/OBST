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
string fileName;
string fileContents;
vector<int> freq;

void processInput(string fname) {
	// read in file contents
	std::ifstream file;
	file.open(fileName + ".dat");
	file.seekg(0, file.end);
	fileContents.reserve(file.tellg());
	file.seekg(0, file.beg);
	fileContents.assign((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	file.close();
	cout << fileContents << endl;
	
	// remove commas from file data string
	fileContents.erase(std::remove(fileContents.begin(), fileContents.end(), ','), fileContents.end());

	// Store tree frequencies in vector
	std::stringstream ss(fileContents);
	int num;
	while (ss >> num) {
		freq.push_back(num);
	}
}

void startTimer() {
	// Both timers are started
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);
}

void timerOutput() {
	// Stop timers.
	QueryPerformanceCounter(&t2);
	int elapsedTime = (t2.QuadPart - t1.QuadPart)* 1000.0 / frequency.QuadPart;
	cout << "Time elapsed for the optimize, tree construction and traversal algorithms: " << elapsedTime << "ms" << endl;
}

int main()
{
	int count = 0;
	OptimalBST obst;
	bool in = false;
	bool cont = true;

	while (cont == true) {
		in = false;
		cout << "Specifications for the Development Environment and Minimum Hardware Requiremesnts:\
				\nComputer Operating System: Windows\
				\nDevelopment Language: C++\
				\nProcessor: AMD or Intel 64-bit\
				\nRAM: 8GB";
		cout << "Enter the filename for the frequency input you would like to use.\
				\nNote that the file should be located in the program directory, and only DAT files are valid.\
				\nDO NOT INCLUDE THE EXTENSION, since we will presume it is a DAT file ==> ";
		
		cin >> fileName;
		processInput(fileName);
		
		if (freq.empty()) {
			cout << "\n\nThis file has no input. Please provide a file with integer frequencies.\n\n";
			continue;
		}
		if (freq.back() == 0) {
			freq.pop_back();
		}
		if (freq.empty()) {
			cout << "\n\nThis file has no valid input. Please provide a file with integer frequencies.\n\n";
			continue;
		}

		// Populate the frequencies into the OptimalBST class instance
		obst.setFrequencies(freq);
		
		// Measure runtime of algorithm
		startTimer();
		
		// Call Optimal Binary Search Tree's optimization algorithm for the frequency inputs.
		// The class will determine the optimal and second optimal trees for the input provided.
		obst.optimizeBST();
		
		// Display the results of the measured runtime for the optimization algorithm.
		timerOutput();
		
		string answer;
		while (in == false) {
			cout << "\nWould you like to read in another input file? (y/n): ";
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
