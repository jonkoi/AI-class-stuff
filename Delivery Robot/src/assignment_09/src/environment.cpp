/*
 * Daniel Vázquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 9
 *
 * environment.cpp
 * */

#include <environment.hpp>
#include <string>
#include <fstream> 
#include <iostream>
#include <agent.hpp>

using namespace std;
Location::Location (float x, float y): x(x), y(y), deadline(0.0)
{}

Location::Location (float x, float y, float deadline):x(x), y(y), deadline(deadline)
{}

Location::~Location()
{}

float Location::get_x()
{
    return x;
}

void Location::set_x(float x_)
{
    x = x_;
}

float Location::get_y()
{
    return y;
}

void Location::set_y(float y_)
{
    y = y_;
}

float Location::get_deadline()
{
    return deadline;
}

void Environment::run()
{
	//first element corresponds to the start position of the robot
	std::vector<Location> scenario1 = read_file("scenario1.txt");
	std::vector<Location> scenario2 = read_file("scenario2.txt");
	std::vector<Location> scenario3 = read_file("scenario3.txt");
	std::vector<Location> scenario4 = read_file("scenario4.txt");
	std::vector<Location> scenario5 = read_file("scenario5.txt");

	int strat = 0;
	int scenario_nr = 0;

	do {
		do {
				cout << "Select an ordering strategy :" << endl;
				cout << "(1) Line number (2) Euclidean distance (3) Time to deadline" << endl;
				cin >> strat;
				if (strat < 1 || strat > 3)
					cout << "Wrong option, please select again" << endl;
			} while (strat < 1 || strat > 3);

			do {
				cout << "Select a scenario (from 1 to 5) : " << endl;
				cin >> scenario_nr;
				if (strat < 1 || strat > 5)
					cout << "Wrong option, please select again" << endl;
			} while (strat < 1 || strat > 5);

			Agent anAgent(scenario1, scenario2, scenario3, scenario4, scenario5, strat, scenario_nr);
			anAgent.run();
	} while (true);

}

std::vector<Location> Environment::read_file(string filename)
{
	ifstream file("./scenarios/" + filename);
	string fileLine;
    string delimiter(" ");
    vector<string> token;
    float x, y;
    int number = -1;
    int pos;
    std::vector<Location> scenario;

    // Read initial position
    if (getline(file, fileLine))
    {
        // Read initial x
        pos = fileLine.find(delimiter);
        x = atof(fileLine.substr(0, pos).c_str());
        fileLine.erase(0, pos + delimiter.length());
        // Read initial y
        pos = fileLine.find(delimiter);
        y = atof(fileLine.substr(0, pos).c_str());
        fileLine.erase(0, pos + delimiter.length());
        // Add starting location to list
        Location newLocation(x, y);
        scenario.push_back(newLocation);
    }
    else
    {
        cout << "Empty file" << endl;
        exit(3);
    }
    // Read rest of file
    while (getline(file, fileLine))
    {
        number++;
        pos = fileLine.find(delimiter);
        do
        {
            token.push_back(fileLine.substr(0, pos));
            fileLine.erase(0, pos + delimiter.length());
            pos = fileLine.find(delimiter);
        }
        while (pos != string::npos);

        token.push_back(fileLine);

        if (number != 0)
        {
            x = atof(token[0].c_str());
            y = atof(token[1].c_str());
            float deadline = atof(token[2].c_str());
            Location newLocation(x, y, deadline);
            // Distance from starting position for sorting
            scenario.push_back(newLocation);
        }
        token.clear();
    }
    return scenario;
}
