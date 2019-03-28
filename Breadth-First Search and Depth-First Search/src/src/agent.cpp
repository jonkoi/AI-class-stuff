/*
 * Foundation from Daniel Vázquez
 * Aritifiacial Intelligence for Robots
 * MAS SS 17
 * Assignment 3
 *
 * agent.cpp
 * */

#include "agent.hpp"

#include <iostream>
#include <stack>
#include <queue>
#include <string>

#include <chrono>
#include <thread>
//#include <ctime>
#include <algorithm>

using namespace std;

Agent::Agent(vector<vector<string> > map, const pair<int, int> initial_pos,
		int number_of_goals, int search_option) :
		map(map), initial_pos(initial_pos), number_of_goals(number_of_goals), search_option(
				search_option), number_of_stored_nodes(0), number_of_visited_nodes(
				0) {

}

Agent::~Agent() {

}

void Agent::run() {

	if (search_option == 1) {
		cout << "Running BFS " << endl;
		cout << "Number of goals " << number_of_goals << endl;
		bfs();
	} else {
		cout << "Running DFS " << endl;
		cout << "Number of goals " << number_of_goals << endl;
		dfs();
	}

}

void Agent::print_map() {
	system("cls");

	for (int row = 0; row < map_rows; row++) {
		for (int col = 0; col < map_cols; col++) {
			cout << map[row][col];
		}
		cout << endl;
	}

	this_thread::sleep_for(chrono::milliseconds(10));

}

void Agent::bfs() {
	//queue stores a pair in the form (row, col)
	queue<pair<int, int> > nodes_queue;
	pair<int, int> current_node;
	//Note: Elements stored in a pair can be accessed by calling the .first and .second attributes. E.g:
	//int row = current_node.first
	//int col = current_node.second

	//Add the initial node to the queue
	//Note: To add a new pair to the queue you can use the std::make_pair method e.g:

	nodes_queue.push(make_pair(initial_pos.first, initial_pos.second));
	number_of_stored_nodes++;
	number_of_visited_nodes++;

	int row;
	int col;

	map[initial_pos.first][initial_pos.second] = "0";

	auto start = std::chrono::steady_clock::now();

	int max_size = nodes_queue.size();

	while (nodes_queue.size() > 0) {
		current_node = nodes_queue.front();
		nodes_queue.pop();
		number_of_stored_nodes--;

		//TODO
		/*Note: If the current node contains a dirt you can
		 * store the position in the goal_positions vector 
		 * by calling the push method e.g goal_positions.push(current_node)
		 */
		row = current_node.first;
		col = current_node.second;

		map[row][col] = "0";
	
		//std::cout << "Start!" << (map[row][col-1]) << "Stop!" << endl;
		//Move up
		if (map[row - 1][col] == " ") {
			//std::cout << "Moved up!" << endl;
			nodes_queue.push(make_pair(row - 1, col));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row - 1][col] = "-";
		}else if (map[row - 1][col] == "*") {
			goal_positions.push_back(make_pair(row - 1, col));
			nodes_queue.push(make_pair(row - 1, col));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row - 1][col] = "-";
		}

		//Move left
		if (map[row][col - 1] == " ") {
			nodes_queue.push(make_pair(row, col - 1));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row][col - 1] = "-";
		}else if (map[row][col - 1] == "*") {
			goal_positions.push_back(make_pair(row, col - 1));
			nodes_queue.push(make_pair(row, col - 1));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row][col - 1] = "-";
		}

		//Move down
		if (map[row + 1][col] == " ") {
			nodes_queue.push(make_pair(row + 1, col));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row + 1][col] = "-";
		}else if (map[row + 1][col] == "*") {
			goal_positions.push_back(make_pair(row + 1, col));
			nodes_queue.push(make_pair(row + 1, col));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row + 1][col] = "-";
		}

		//Move right
		if (map[row][col + 1] == " ") {
			nodes_queue.push(make_pair(row, col + 1));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row][col + 1] = "-";
		}else if (map[row][col + 1] == "*") {
			goal_positions.push_back(make_pair(row, col + 1));
			nodes_queue.push(make_pair(row, col + 1));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row][col + 1] = "-";
		}

		max_size = max_size > nodes_queue.size() ? max_size : nodes_queue.size();

		print_map();
		cout << "Visited nodes: " << number_of_visited_nodes++ << endl;

		if (goal_positions.size() == number_of_goals) {
			break;
		}


	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> diff = end - start;

	print_evaluation_metrics("queue", diff, max_size);
}

void Agent::dfs() {
	//the stack stores a pair in the form (row, col)
	stack<pair<int, int> > nodes_stack;
	pair<int, int> current_node;
	//Note: Elements stored in a pair can be accessed by calling the .first and .second attributes. E.g:
	//int row = current_node.first
	//int col = current_node.second

	//Add the initial node to the stack
	//Note: To add a new pair to the stack you can use the std::make_pair method e.g:
	nodes_stack.push(make_pair(initial_pos.first, initial_pos.second));
	number_of_stored_nodes++;
	number_of_visited_nodes++;

	int row;
	int col;


	map[initial_pos.first][initial_pos.second] = "0";

	auto start = std::chrono::steady_clock::now();

	int max_size = nodes_stack.size();

	while (nodes_stack.size() > 0) {

		

		current_node = nodes_stack.top();
		nodes_stack.pop();
		number_of_stored_nodes--;

		//TODO
		/*Note: If the current node contains a dirt you can 
		 * store the position in the goal_positions vector 
		 * by calling the push method e.g goal_positions.push(current_node)
		 */

		row = current_node.first;
		col = current_node.second;

		map[row][col] = "0";

		if (map[row - 1][col] == " ") {
			//std::cout << "Moved up!" << endl;
			nodes_stack.push(make_pair(row - 1, col));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row - 1][col] = "-";
		}
		else if (map[row - 1][col] == "*") {
			goal_positions.push_back(make_pair(row - 1, col));
			nodes_stack.push(make_pair(row - 1, col));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row - 1][col] = "-";
		}

		//Move left
		if (map[row][col - 1] == " ") {
			nodes_stack.push(make_pair(row, col - 1));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row][col - 1] = "-";
		}
		else if (map[row][col - 1] == "*") {
			goal_positions.push_back(make_pair(row, col - 1));
			nodes_stack.push(make_pair(row, col - 1));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row][col - 1] = "-";
		}

		//Move down
		if (map[row + 1][col] == " ") {
			nodes_stack.push(make_pair(row + 1, col));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row + 1][col] = "-";
		}
		else if (map[row + 1][col] == "*") {
			goal_positions.push_back(make_pair(row + 1, col));
			nodes_stack.push(make_pair(row + 1, col));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row + 1][col] = "-";
		}

		//Move right
		if (map[row][col + 1] == " ") {
			nodes_stack.push(make_pair(row, col + 1));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row][col + 1] = "-";
		}
		else if (map[row][col + 1] == "*") {
			goal_positions.push_back(make_pair(row, col + 1));
			nodes_stack.push(make_pair(row, col + 1));
			number_of_stored_nodes++;
			number_of_visited_nodes++;
			map[row][col + 1] = "-";
		}

		max_size = max_size > nodes_stack.size() ? max_size : nodes_stack.size();

		

		print_map();
		cout << "Visited nodes: " << number_of_visited_nodes++ << endl;

		if (goal_positions.size() == number_of_goals) {
			break;
		}
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> diff = end - start;

	print_evaluation_metrics("stack", diff, max_size);

}

void Agent::print_evaluation_metrics(string data_structure_name, std::chrono::duration<double> diff, int max_size) {
	print_map();
	cout << "All the possible nodes have been explored " << endl;
	cout << "Found " << goal_positions.size() << " of " << number_of_goals
			<< endl;
	cout << "Maximum size of the " << data_structure_name << " : "
			<< max_size << endl;
	cout << "Number of stored nodes: " << number_of_stored_nodes << endl;
	cout << "Total of visited nodes: " << number_of_visited_nodes << endl;
	cout << "Running time: " << diff.count() << endl;
	print_goal_positions();


	//Test code
	//int temp = 0;

	//for (int row = 0; row < map_rows; row++) {
	//	for (int col = 0; col < map_cols; col++) {
	//		if (map[row][col] == "0" || map[row][col] == "-") {
	//			map[row][col] = "X";
	//			temp++;
	//			print_map();
	//			cout << "Test: " << temp << endl;
	//		}
	//	}
	//}

	//cout << "Test: " << temp << endl;
}

void Agent::print_goal_positions() {
	cout << "Goals: " << endl;
	for (int i = 0; i < goal_positions.size(); i++) {
		cout << i + 1 << ": (" << goal_positions[i].first << ", "
				<< goal_positions[i].second << ")" << endl;
	}
}

