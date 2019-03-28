/*
 * Foundation from Daniel Vazquez
 * Aritificial Intelligence for Robotics
 * SS 17
 * Assignment 5
 *
 * agent.cpp
 * */

#include "agent.hpp"

#include <iostream>
#include <string>
//#include <unistd.h>
#include <windows.h>
#include <chrono>
#include <thread>

#define map_rows 25
#define map_cols 141

using namespace std;

Agent::Agent
    (
    vector<vector<string>> selected_map,
    const pair<int,int> initial_pos,
    int number_of_goals
    ):
    empty_map(selected_map),
    map(selected_map),
    initial_pos(initial_pos),
	start_pos(initial_pos),
    number_of_goals(number_of_goals),
    max_number_of_stored_nodes(0),
    number_of_visited_nodes(0),
    total_of_stored_nodes(0),
    deepest_level(0)
{
    max_limit = map_rows * map_cols;
	//max_limit = 20;
    print_map(empty_map);
}

Agent::~Agent()
{
}

void Agent::run()
{
    cout << "Running IDFS " << endl;
    cout << "Number of goals " << number_of_goals << endl;
    Sleep(1000);
    iterative_deepening_search();
}

void Agent::print_map(vector<vector<string>>& a_map)
{
    system("cls");
    int row = initial_pos.first;
    int col = initial_pos.second;

    for(int row = 0; row < map_rows; row++)
    {
        for(int col = 0; col < map_cols; col++)
        {
            cout << a_map[row][col];
        }    
        cout << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(20));
}


bool Agent::recursive_dls(pair<int,int> current_node, int goal, int current_level,
                          int limit, vector<pair<int,int>>& current_path)
{
    //TODO
    
    //Notes: 
    //Backtrack from here once you have found a goal.
    //If you have found a goal, do not forget to get a fresh copy of the map.
    //Stop searching if you have found a goal or reached the depth limit.
    //Only return true if a goal has been found.
	//Sleep(1000);
	bool result = false;
	bool cutoff_occured = false;

	int row = current_node.first;
	int col = current_node.second;

	string node_content = map[row][col];
	map[row][col] = "0";
	number_of_visited_nodes++;
	current_path.push_back(current_node);

	//cout << current_path.size() << endl;
	//for (int i = 0; i < current_path.size(); i++) {
	//	cout << "[" << current_path[i].first << " " << current_path[i].second << "]" << endl;
	//}

	if (node_content == to_string(goal)) {
		start_pos.first = row;
		start_pos.second = col;
		return true;
	}
	else if (current_level == limit) {
		return false;
	}
	else {
		// Right, down, left, up
		//Right first seem better for these maps
		if (map[row][col + 1] != "|" && map[row][col + 1] != "=" && map[row][col + 1] != "0") {
			pair<int, int> next_node = make_pair(row, col + 1);
			result = recursive_dls(next_node, goal, current_level + 1, limit, current_path);
			if (result == false) {
				current_path.pop_back();
			}
			else {
				/*backtrack_path(current_path);
				cout << "BACKTRACKING" << endl;*/
				return true;
			}
		}
		if (map[row + 1][col] != "|" && map[row + 1][col] != "=" && map[row + 1][col] != "0") {
			pair<int, int> next_node = make_pair(row + 1, col);
			result = recursive_dls(next_node, goal, current_level + 1, limit, current_path);
			if (result == false) {
				current_path.pop_back();
			}
			else {
				/*backtrack_path(current_path);
				cout << "BACKTRACKING" << endl;*/
				return true;
			}
		}
		if (map[row][col - 1] != "|" && map[row][col - 1] != "="&& map[row][col - 1] != "0") {
			pair<int, int> next_node = make_pair(row, col - 1);
			result = recursive_dls(next_node, goal, current_level + 1, limit, current_path);
			if (result == false) {
				current_path.pop_back();
			}
			else {
				//backtrack_path(current_path);
				//cout << "BACKTRACKING" << endl;
				return true;
			}
		}
		if (map[row - 1][col] != "|" && map[row - 1][col] != "=" && map[row - 1][col] != "0") {
			pair<int, int> next_node = make_pair(row - 1, col);
			result = recursive_dls(next_node, goal, current_level + 1, limit, current_path);
			if (result == false) {
				current_path.pop_back();
			}
			else {
				/*backtrack_path(current_path);
				cout << "BACKTRACKING" << endl;*/
				return true;
			}
		}
	}
    return false;
}

bool Agent::depth_limited_seach(int limit, int goal)
{
	map = empty_map;
    vector<pair<int,int>> current_path; 
	pair<int, int> current_node = start_pos;
	bool result = false;
	int current_level = 0;
	deepest_level = limit;
	number_of_visited_nodes = 0;
	result = recursive_dls(current_node, goal, current_level, limit, current_path);
	if (result == true) {
		temp_path = current_path;
	}
	/*for (int i = 0; i < current_path.size(); i++) {
		cout << "[" << current_path[i].first << " " << current_path[i].second << "]" << endl;
	}*/
    return result;
}

void Agent::iterative_deepening_search()
{
	for (int goal = 1; goal < number_of_goals + 1; goal++) {
		map = empty_map;

		bool result = false;
		
		for (int limit = 0; limit <= max_limit; limit++) {
			result = depth_limited_seach(limit, goal);
			if (result == true) break;
		}

		backtrack_path(temp_path);
		print_final_results();

		if (result == true) {
			//SUCCESS
			cout << "SUCCESS in finding goal number " << goal << endl;
			Sleep(3000);
		} else {
			//FAILED
			cout << "Can't find goal. Skip to next one." << endl;
			Sleep(3000);
		}
		
	}

	cout << "!!!!!DONE!!!!!!! " << endl;
}

void Agent::print_final_results()
{
    cout << "Deepest level reached: " << deepest_level  << endl;
    cout << "Total of stored nodes: " << total_of_stored_nodes << endl;
    cout << "Total of visited nodes: " << number_of_visited_nodes << endl;
}

void Agent::backtrack_path(vector<pair<int,int>> current_path)
{
    //use the original map to backtrace
    vector<vector<string>> local_map = empty_map;
    
    pair<int,int> current_data; 
    //TODO
    //Backtrace. Use the current path vector to set the path on the map. 
	total_of_stored_nodes = current_path.size();
	for (int i = 0; i < current_path.size(); i++) {
		local_map[current_path[i].first][current_path[i].second] = "0";
	}
    //print backtraced path
    print_map(local_map);
}
