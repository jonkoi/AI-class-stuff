/*
 * Daniel Vázquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 7
 *
 * environment.cpp
 * */

#include <world.hpp>
#include <string>
#include <fstream> 
#include <iostream>
#include "matplotlibcpp.h"
using namespace std;

World::World(string filename)
{
    readCitiesFromFile(filename);
}

World::~World()
{}

int World::getNumCities()
{
    return numCities;
}

void World::readCitiesFromFile(string filename)
{
	ifstream file(filename);
	string line;
    string delimiter(",");
    vector<string> token;
    string cityName;
    float x, y;
    int number = -1;

    while (getline(file, line)) {
        number++;
        size_t pos = line.find(delimiter);
        do {
            token.push_back(line.substr(0, pos));
            line.erase(0, pos + delimiter.length());
            pos = line.find(delimiter);

        } while (pos != string::npos);

        token.push_back(line);

        if (number != 0) { //First line of the file is a comment
            cityNames.push_back(token[0]);
            x = atof(token[1].c_str());
            y = atof(token[2].c_str());
            pair<float,float> coord = {x,y};
            coordinates.push_back(coord);        
        }
        token.clear();
    }
    file.close();
    numCities = number;
}

void World::saveCyclePlot(vector<int> cycle, string filename)
{
    vector<float> x,y;
    for (auto &cityIndex : cycle)
    {
        x.push_back(coordinates[cityIndex].first);
        y.push_back(coordinates[cityIndex].second);
    }
    matplotlibcpp::plot(x, y);
    matplotlibcpp::save(filename);
}

void World::cyclePlot(vector<int> cycle)
{
    vector<float> x,y;
    for (auto &cityIndex : cycle)
    {
        x.push_back(coordinates[cityIndex].first);
        y.push_back(coordinates[cityIndex].second);
    }
    matplotlibcpp::plot(x, y);
    matplotlibcpp::show();
}

vector<pair<float,float>> World::getCoordinates(){
	return coordinates;
}
