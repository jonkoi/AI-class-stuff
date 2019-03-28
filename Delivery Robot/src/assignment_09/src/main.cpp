/*
 * Daniel Vázquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 8
 *
 * main.cpp
 * */
 
#include <iostream>
#include <chrono>
#include <agent.hpp>
#include <environment.hpp>

using ms = chrono::milliseconds;
using namespace std;

int main(int argc, char* argv[]) {
	//Assuming the distance is the same as the traveling duration

    Environment env;

    vector<Location> a = env.read_file("scenario1.txt");
    env.run();
    return 0;
}
