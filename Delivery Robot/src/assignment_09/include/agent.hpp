/*
 * Daniel Vázquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 9
 *
 * agent.hpp
 * */

#ifndef Agent_H_
#define Agent_H_

#include <vector>
#include <fstream>
#include <environment.hpp>

using namespace std;

class Agent
{
    private:
        vector<Location> scenario;
        vector<pair<Location, float>> dbs_backtracking(vector<Location> scenario);
        float find_cost(Location current_loc, Location next_loc);
        vector<pair<Location, float>> recursive_dbs(vector<pair<Location, float>> assignment, vector<Location> scenario,Location current_loc, float current_cost);
        vector<Location> choose_scenario(int scenario);
        vector<Location> order_scenario(vector<Location> start_scenario, int strat);
        bool euclidean_comparator(Location i, Location j);
        bool time_comparator(Location i, Location j);
        vector<Location> time_sort(vector<Location> scenario);
        vector<Location> dist_sort(vector<Location> scenario);
        vector<Location> scenario1, scenario2, scenario3, scenario4, scenario5;
        int strat;
        int scenario_nr;
        bool solution_found;
        long eval;


        //first element corresponds to the start position of the robot

    public:
        Agent(vector<Location> scenario1,
              vector<Location> scenario2,
              vector<Location> scenario3,
              vector<Location> scenario4,
              vector<Location> scenario5,
              int strat,
              int scenario_nr);
        ~Agent();
        void run();
        void print_scenario(vector<Location>&);
        void print_assignment(vector<pair<Location, float>>&, vector<Location> scenario);
//        bool solution_found;
        Location start_location;

        struct time_compare {

        };

};

#endif // Agent_H_
