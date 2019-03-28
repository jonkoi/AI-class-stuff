/*
 * Daniel Vázquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 7
 *
 * agent.cpp
 * */
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <agent.hpp>
#include <unistd.h>
using namespace std;

Agent::Agent(vector<int> startCycle, vector<pair<float,float>> coordinates) :
		currentCost(0), startCycle(startCycle), coordinates(coordinates), resultCycle(startCycle)
{
	resultCost = findCost(startCycle);
}

Agent::~Agent()
{}

vector<int> Agent::simpleHillClimb()
{
	clock_t start = clock();
	for (int i = 0; i < 50; i++){
		currentCycle = startCycle;

		srand(i+100);
		random_shuffle(currentCycle.begin(), currentCycle.end());
		currentCost = findCost(currentCycle);
		cout << "-------"<<endl;
		cout << "Start cost: " << currentCost <<endl;

		find_local_min = false;

		int num = 0;
		while (!find_local_min){
			break_outer_loop = false;
			for (int x = 0; x < currentCycle.size() - 1; x++){
				if (!break_outer_loop){
					for (int y = x + 1; y < currentCycle.size(); y++){
						num++;
						vector<int> tempCycle = currentCycle;
						swap(tempCycle[x], tempCycle[y]);
						float tempCost = findCost(tempCycle);

						if (tempCost < currentCost){
							currentCost = tempCost;
							currentCycle = tempCycle;
							break_outer_loop = true;
							break;
						}

						if ((x == currentCycle.size()-2) && (y == currentCycle.size()-1)){
							find_local_min = true;
							break_outer_loop = true;
						}
					}
				} else {
					break;
				}
			}
		}

		cout << num <<endl;


		cout << "End cost: " << currentCost <<endl;
		if (resultCost > currentCost){
			resultCost = currentCost;
			resultCycle = currentCycle;
		}
		cout << "Current result cost: " << resultCost <<endl;

	}

	cout << "Time: " << (clock() - start) / (double)CLOCKS_PER_SEC << endl;
	return resultCycle;

}
vector<int> Agent::steepestAscendHillClimb()
{
	clock_t start = clock();
	for (int i = 0; i < 50; i++){
		currentCycle = startCycle;

		srand(i+100);
		random_shuffle(currentCycle.begin(), currentCycle.end());
		currentCost = findCost(currentCycle);
		cout << "-------"<<endl;
		cout << "Start cost: " << currentCost <<endl;

		find_local_min = false;

		int num = 0;
		while (!find_local_min){
			find_local_min = true;
			float temp_currentCost = currentCost;
			vector<int> temp_currentCycle = currentCycle;
			for (int x = 0; x < currentCycle.size() - 1; x++){
				for (int y = x + 1; y < currentCycle.size(); y++){
					num++;
					vector<int> tempCycle = currentCycle;
					swap(tempCycle[x], tempCycle[y]);
					float tempCost = findCost(tempCycle);

					if (tempCost < temp_currentCost){
						temp_currentCost = tempCost;
						temp_currentCycle = tempCycle;
						find_local_min = false;
					}
				}
			}

			currentCost = temp_currentCost;
			currentCycle = temp_currentCycle;
		}

		cout << num <<endl;


		cout << "End cost: " << currentCost <<endl;
		if (resultCost > currentCost){
			resultCost = currentCost;
			resultCycle = currentCycle;
		}
		cout << "Current result cost: " << resultCost <<endl;
	}

	cout << "Time: " << (clock() - start) / (double)CLOCKS_PER_SEC << endl;
	return resultCycle;
}

double getTemperature(int seconds, int time, int amplitude)
{
	return (((double)(seconds - time)/ seconds)*amplitude);
}

vector<int> Agent::simulatedAnnealing(int minutes)
{

	int seconds = minutes * 60;

	time_t start = time(NULL);
	time_t end = start + seconds;

	currentCycle = startCycle;
	random_shuffle(currentCycle.begin(), currentCycle.end());
	float tempCost = currentCost;
	vector<int> tempCycle = currentCycle;

	int i = 1;

	int x, y;

	while (time(NULL) < end) {
//		usleep(1000000);
		srand(time(NULL) + i);

		tempCycle = currentCycle;
		currentCost = findCost(currentCycle);

		x = rand() % tempCycle.size();
		y = rand() % tempCycle.size();

		swap(tempCycle[x], tempCycle[y]);
		tempCost = findCost(tempCycle);

		if (currentCost > tempCost){
			currentCost = tempCost;
			currentCycle = tempCycle;
		} else {
			double temp = getTemperature(seconds, time(NULL)-start, 75);
			double ratio = exp((currentCost - tempCost) / temp);
			double threshold = ((double) rand() / (RAND_MAX));

//			cout << "Temp: " << temp << endl;
//			cout << "Diff: " << (currentCost - tempCost) << endl;
//			cout << "Threshold:" << threshold <<endl;
//			cout << "Ratio: " << ratio << endl;

			if (ratio > threshold){
				currentCost = tempCost;
				currentCycle = tempCycle;
			}
		}

		i++;
		cout << "Result Cost: " << currentCost << endl;

	}
	cout << "Iterations" << i <<endl;
	cout << "Time: " << (time(NULL) - start)<< endl;
	return currentCycle;
}



template <typename T,typename U>
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {
    return {pow(l.first-r.first, 2.0),pow(l.second-r.second, 2.0)};
}

float Agent::findCost(vector<int> cycle)
{
	//Assuming the length between end and start is not important
	int cost = 0;
	for (int i = 0; i < cycle.size() - 1; i++){
		pair<float,float> norm2_pair = coordinates[cycle[i]] - coordinates[cycle[i+1]];
		cost += sqrt(norm2_pair.first + norm2_pair.second);

//		cost += sqrt(pow(coordinates[cycle[i + 1]].first - coordinates[cycle[i]].first, 2)
//								    + pow(coordinates[cycle[i + 1]].second - coordinates[cycle[i]].second, 2));
	}
//	pair<float,float> norm2_pair_last = coordinates[cycle[0]] - coordinates[cycle[cycle.size()-1]];
//	cost += sqrt(norm2_pair_last.first + norm2_pair_last.second);
	return cost;
}
