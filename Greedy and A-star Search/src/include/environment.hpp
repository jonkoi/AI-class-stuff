/*
 * Foundation from Daniel Vazquez
 * Aritificial Intelligence for Robotics
 * SS 17
 * Assignment 6
 *
 * env.hpp
 * */

#ifndef ENV_H
#define ENV_H

#include <vector> 

#define NUM_COLS 3
#define NUM_ROWS 3

using namespace std;

class Environment {
public:
	Environment();
	~Environment() {}
	void run();

private:
	vector<vector<int>> puzzle;

	void generate_puzzle();
	void print_puzzle();
};
#endif
