/*
 * Foundation from Daniel Vazquez
 * Aritificial Intelligence for Robotics
 * SS 17
* Assignment 6
*
* agent.cpp
* */
#include "agent.hpp"
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
#include <functional>
#include <time.h>
#include <ctime>
#include <stdio.h>
#include <Windows.h>

using namespace std;

//Reference: https://github.com/ani94/8-puzzle-solver-cpp

Agent::Agent(Puzzle puzzle, Solver solver, Heuristic heuristic) :
	puzzle(puzzle), solver(solver), heuristic(heuristic), dx({ -1,+1,0,0 }), dy({ 0,0,-1,+1 })
{}

Agent::~Agent()
{}

void Agent::run()
{
	if (solver == Solver::GREEDY)
	{
		cout << "Solver: Greedy Search" << endl;
		if (heuristic == Heuristic::MISPLACED_TILES) {
			cout << "Heuristic: Misplaced tiles" << endl;
		}

		else {
			cout << "Heuristic: Manhattan distance" << endl;
		}
		greedy_search(heuristic);
	}
	if (solver == Solver::A_STAR)
	{
		cout << "Solver: A*" << endl;
		if (heuristic == Heuristic::MISPLACED_TILES)
		{
			cout << "Heuristic: Misplaced tiles" << endl;
		}
		else
		{
			cout << "Heuristic: Manhattan distance" << endl;
		}
		a_star(heuristic);
	}
}

int Agent::misplaced_tiles(Puzzle puzzle) {
	//TODO
	int misplaced = 0;
	for (int i = 0; i < 9; i++) {
		int row = floor(i / 3);
		int col = i % 3;

		if (puzzle[row][col] != i + 1 && puzzle[row][col] != 0) {
			misplaced++;
		}
	}
	return misplaced;
}

int Agent::manhattan_distance(Puzzle puzzle) {
	//TODO
	int manhattan = 0;
	for (int i = 0; i < 9; i++) {
		int row = floor(i / 3);
		int col = i % 3;

		if (puzzle[row][col] != 0) {
			int row_dist = abs(row - floor((puzzle[row][col] - 1) / 3));
			int col_dist = abs(col - (puzzle[row][col] - 1) % 3);
			manhattan = manhattan + row_dist + col_dist;
		}
	}
	return manhattan;

}

bool Agent::expandable(int i, int j) {
	if (i >= 0 && i <= 2 && j >= 0 && j <= 2)
		return true;
	else
		return false;
}

struct cmp1
{
	bool operator()(const State& a, const State& b)
	{
		return a.second.first > b.second.first;
	}
};
struct cmp2
{
	bool operator()(const State& a, const State& b)
	{
		return a.second.first + a.second.second > b.second.first + b.second.second;
	}
};


vector<Puzzle> Agent::expand(Puzzle puzzle) {

	vector<Puzzle> next_states;
	Puzzle temp_puzzlezle = puzzle;
	pair<int, int> pos;
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			if (puzzle[i][j] == 0)
			{
				pos.first = i;
				pos.second = j;
				break;
			}
		}
	}

	for (int k = 0; k<4; k++)
	{
		int cx = pos.first;
		int cy = pos.second;
		if (expandable(cx + dx[k], cy + dy[k])) {
			Puzzle successor = temp_puzzlezle;
			swap(successor[cx + dx[k]][cy + dy[k]], successor[cx][cy]);
			next_states.push_back(successor);
		}
	}

	return next_states;
}

void Agent::greedy_search(Heuristic heuristic) {
	//TODO
	//Note: In this assignment you must find the proper way to
	//keep track of repeated states.
	clock_t start = clock();

	priority_queue<State, vector<State>, cmp1> Q;
	int (Agent::*get_distance)(Puzzle);
	set<string> visited_nodes;

	int total_visited_nodes = 0;
	int iteration = 0;

	get_distance = heuristic == Heuristic::MISPLACED_TILES ?
		&Agent::misplaced_tiles : &Agent::manhattan_distance;

	pair<int, int> expected_distance = { (this->*get_distance)(puzzle),0 };
	State initial_state(puzzle, expected_distance);

	Q.push(initial_state);
	while (!Q.empty()) {
		iteration++;
		State current_node = Q.top();
		Q.pop();
		Puzzle temp_puzzle = current_node.first;
		pair<int, int> cost_pair = current_node.second;

		string string_rep = get_string_reps(temp_puzzle);

		/*cout << string_rep << endl;*/
		if (visited_nodes.find(string_rep) == visited_nodes.end()) {
			total_visited_nodes++;
			visited_nodes.insert(string_rep);

			if (cost_pair.first == 0) {
				print_puzzle(temp_puzzle);
				cout << "Total Vistited: " << total_visited_nodes << endl;
				cout << "Iterations: " << iteration << endl;
				break;
			}

			vector<Puzzle> successors = expand(current_node.first);
			for (auto &board : successors) {
				expected_distance = { (this->*get_distance)(board), 0 };
				Q.push({ board, expected_distance });
			}
		}
	}

	cout << "Time: " << (clock() - start) / (double)CLOCKS_PER_SEC << endl;
}

void Agent::a_star(Heuristic heuristic) {
	//TODO
	//Note: In this assignment you must find the proper way to
	//keep track of repeated states.
	clock_t start = clock();

	priority_queue<State, vector<State>, cmp2> Q;
	int (Agent::*get_distance)(Puzzle);
	set<string> visited_nodes;

	int total_visited_nodes = 0;
	int sum_cost = 0;
	int iteration = 0;

	get_distance = heuristic == Heuristic::MISPLACED_TILES ?
		&Agent::misplaced_tiles : &Agent::manhattan_distance;

	pair<int, int> total_cost_pair = { (this->*get_distance)(puzzle),0 };
	State initial_state(puzzle, total_cost_pair);

	Q.push(initial_state);
	while (!Q.empty()) {
		iteration++;
		State current_node = Q.top();
		Q.pop();
		Puzzle temp_puzzle = current_node.first;
		pair<int, int> cost_pair = current_node.second;
		//sum_cost = sum_cost + (this->*get_distance)(temp_puzzle);
		sum_cost = cost_pair.second;

		string string_rep = get_string_reps(temp_puzzle);

		/*cout << string_rep << endl;*/

		if (visited_nodes.find(string_rep) == visited_nodes.end()) {
			total_visited_nodes++;
			visited_nodes.insert(string_rep);

			if (cost_pair.first == 0) {
				print_puzzle(temp_puzzle);
				cout << "Path Cost: " << sum_cost << endl;
				cout << "Total Vistited: " << total_visited_nodes << endl;
				cout << "Iterations: " << iteration << endl;
				break;
			}

			vector<Puzzle> successors = expand(current_node.first);
			for (auto &board : successors) {
				total_cost_pair = { (this->*get_distance)(board), current_node.second.second + 1 };
				Q.push({ board, total_cost_pair });
			}
		}
	}

	cout << "Time: " << (clock() - start) / (double)CLOCKS_PER_SEC << endl;
}

void Agent::print_puzzle(Puzzle& puzzle) {
	for (int rows = 0; rows < NUM_ROWS; rows++) {
		for (int cols = 0; cols < NUM_COLS; cols++) {
			std::cout << "|" << puzzle[rows][cols];
		}
		std::cout << "|" << std::endl;
	}
}

string Agent::get_string_reps(Puzzle puzzle) {
	string rep = "";
	for (int row = 0; row<NUM_ROWS; row++) {
		for (int col = 0; col<NUM_COLS; col++) {
			hash += to_string(puzzle[row][col]);
		}
	}
	return rep;
}
