/*
 * Daniel Vázquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 9
 *
 * environment.cpp
 * */

#ifndef ENV_H_
#define ENV_H_

#include <string>
#include <vector>

using namespace std;

class Location
{
    public:
        Location(float x, float y);
        Location(float x, float y, float deadline);
        ~Location();
        float get_x();
        void set_x(float coord);
        float get_y();
        void set_y(float coord);
        float get_deadline();

    private:
        float x;
        float y;
        float deadline;
};

class Environment
{
    public:
        Environment() {}
        ~Environment() {}
        void run();
        vector<Location> read_file(string filename);

    private:
        vector<Location> cities;
};
#endif /* ENV_H_ */
