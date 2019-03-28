/*
 * Foundation from Daniel Vazquez
 * Aritificial Intelligence for Robotics
 * SS 17
 * Assignment 6
 *
 * agent.hpp
 * */

#ifndef AGENT_HPP
#define AGENT_HPP

#include <vector>
#include <string>
#include <utility> 

#define NUM_COLS 3
#define NUM_ROWS 3

using namespace std;

typedef vector<vector<int>> Puzzle;
typedef pair<Puzzle, pair<int, int>> State;

enum Heuristic{
    MISPLACED_TILES,
    MANHATTAN_DISTANCE
};

enum Solver{
    GREEDY,
    A_STAR
};

class Agent {
public:
	Agent(Puzzle puzzle, Solver solver, Heuristic heuristic);
	~Agent();
	void run();

private:
	vector<vector<int>> puzzle;

	Solver solver;
	Heuristic heuristic;

	vector<int> dx;
	vector<int> dy;

	void greedy_search(Heuristic heuristic);
	void a_star(Heuristic heuristic);
	int misplaced_tiles(Puzzle puzzle);
	int manhattan_distance(Puzzle puzzle);

	vector<Puzzle>expand(Puzzle puzzle);
	bool expandable(int i, int j);
	string get_string_reps(Puzzle puzzle);

	void print_puzzle(Puzzle& puzzle);
};

#endif
