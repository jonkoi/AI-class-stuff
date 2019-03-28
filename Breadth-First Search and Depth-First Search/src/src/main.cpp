/*
 * Foundation from Daniel Vázquez
 * Aritifiacial Intelligence for Robots
 * MAS SS 17
 * Assignment 3
 *
 * main.cpp
 * */
#include <iostream>
#include <thread>
#include <chrono>

#include "environment.hpp"

int main(int arc, char* argv[])

{
	Environment anEnvironment;
	anEnvironment.run();

	getchar();
	getchar();
	return 1;
}
