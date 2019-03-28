/*
 * Daniel Vázquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 9
 *
 * agent.cpp
 * */
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <agent.hpp>
#include <utility>
#include <math.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>

using namespace std;

Agent::Agent(vector<Location> scenario1,
             vector<Location> scenario2,
             vector<Location> scenario3,
             vector<Location> scenario4,
             vector<Location> scenario5,
             int strat,
             int scenario_nr) :
             scenario1(scenario1),
             scenario2(scenario2),
             scenario3(scenario3),
             scenario4(scenario4),
             scenario5(scenario5),
             strat(strat),
             scenario_nr(scenario_nr),
             solution_found(false),
             start_location(scenario1[0]),
             eval(0)
{}

Agent::~Agent()
{}

void Agent::run()
{
	//example
	vector<Location>start_scenario = choose_scenario(scenario_nr);
	start_location = start_scenario[0];
	cout << "-------------" << endl;
	vector<Location> cur_scenario = order_scenario(start_scenario, strat);
	print_scenario(cur_scenario);
	cout << "-------------" << endl;
	vector<pair<Location, float>> result = dbs_backtracking(cur_scenario);
	print_assignment(result, cur_scenario); //first element corresponds to the start position of the robot
	cout << "Number of evaluations: " << eval <<endl;
    //TODO
}

void Agent::print_scenario(vector<Location>& scenario)
{
    std::vector<double> x, y;
    for (int i = 0; i < scenario.size(); i++)
    {
        std::cout << "Location: " << scenario[i].get_x() << "," << scenario[i].get_y() <<
                     " Deadline: " << scenario[i].get_deadline() << std::endl;
    }
}

void Agent::print_assignment(vector<pair<Location, float>>& assignment, vector<Location> scenario)
{
    std::vector<double> x, y;
    if (assignment.size() ==  0){
		cout << "Can't find solution!!!" << endl;
	}
    for (int i = 0; i < assignment.size(); i++)
    {

        std::cout << "Location: " << assignment[i].first.get_x() << "," << assignment[i].first.get_y() <<
                     " Deadline: " << assignment[i].first.get_deadline() << " Duration: " << assignment[i].second << std::endl;
    }
}

vector<pair<Location, float>> Agent::dbs_backtracking(vector<Location> scenario)
{
    //TODO
	std::vector<pair<Location, float>> assignment;
	pair<Location, float> a = make_pair(start_location, 0);
	assignment.push_back(a);
	scenario.erase(scenario.begin());
	print_scenario(scenario);
	cout << "-------------" << endl;
	vector<pair<Location, float>> final_assignment = recursive_dbs(assignment, scenario, start_location, 0);
	return final_assignment;
}

vector<pair<Location, float>> Agent::recursive_dbs(vector<pair<Location, float>> assignment, vector<Location> scenario, Location current_loc, float current_cost){
	if (scenario.size() == 0){
		solution_found = true;
		return assignment;
	}
	for(int i = 0; i < scenario.size(); i++){
		eval++;
		vector<Location> temp_scenario = scenario;
		Location next_loc = temp_scenario[i];
		temp_scenario.erase(temp_scenario.begin() + i);

		float cost = find_cost(current_loc, next_loc);

		if (current_cost + cost <= next_loc.get_deadline()){
			pair<Location, float> p = make_pair(next_loc, current_cost + cost);
			assignment.push_back(p);
			assignment = recursive_dbs(assignment, temp_scenario, next_loc, current_cost + cost);
			if (solution_found == true){
				return assignment;
			}
		}
	}
	assignment.pop_back();
	return assignment;
}

float Agent::find_cost(Location current_loc, Location next_loc){
	float x_diff = current_loc.get_x() - next_loc.get_x();
	float y_diff = current_loc.get_y() - next_loc.get_y();

	float cost = sqrt(pow(x_diff,2) + pow(y_diff,2));

	return cost;
}

float find_cost(Location current_loc, Location next_loc){
	float x_diff = current_loc.get_x() - next_loc.get_x();
	float y_diff = current_loc.get_y() - next_loc.get_y();

	float cost = sqrt(pow(x_diff,2) + pow(y_diff,2));

	return cost;
}

vector<Location> Agent::choose_scenario(int scenario_nr){
	switch(scenario_nr){
		case 1:
			return scenario1;
		case 2:
			return scenario2;
		case 3:
			return scenario3;
		case 4:
			return scenario4;
		case 5:
			return scenario5;
	}
}

bool Agent::euclidean_comparator(Location a, Location b){
	return (find_cost(a, start_location) < find_cost(b, start_location));
}

bool Agent::time_comparator(Location i, Location j){
	return (i.get_deadline() < j.get_deadline());
}

vector<Location> Agent::time_sort(vector<Location> scenario){
	sort(scenario.begin()+1, scenario.end(), boost::bind(&Agent::time_comparator, this, _1, _2));
	return scenario;
}

vector<Location> Agent::dist_sort(vector<Location> scenario){
	sort(scenario.begin()+1, scenario.end(), boost::bind(&Agent::euclidean_comparator, this, _1, _2));
	return scenario;
}

//struct {
//   bool operator()(Location a, Location b) const
//   {
//	   return (a.get_deadline() < b.get_deadline());
//   }
//} time_comparator;
//
//struct {
//   bool operator()(Location a, Location b) const
//   {
//	   return (find_cost(a, start) < find_cost(b, start_location));
//   }
//} euclidean_comparator;

vector<Location> Agent::order_scenario(vector<Location> start_scenario, int strat){
	if (strat == 2){
//		sort(start_scenario.begin()+1, start_scenario.end(), bind(&Agent::euclidean_comparator, this));
		vector<Location> cur_scenario = dist_sort(start_scenario);
		return cur_scenario;
	} else if (strat == 3) {
//		sort(start_scenario.begin()+1, start_scenario.end(), time_comparator);
		vector<Location> cur_scenario = time_sort(start_scenario);
		return cur_scenario;
	}
	return start_scenario;
}
