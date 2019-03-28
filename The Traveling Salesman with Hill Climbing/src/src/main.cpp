#include <iostream>
#include <vector>
#include <algorithm> // contains std::random_shuffle to initialize a cycle
#include <agent.hpp>
#include <world.hpp>
using namespace std;

int main(int argc, char* argv[]) { 
    // Simple usage example
    World myWorld = World("./input/49_cities.txt");
    cout << "number of cities: " << myWorld.getNumCities() << endl;

    // create random cycle
    vector<int> startCycle;
    for (int i = 0; i < myWorld.getNumCities(); i++) startCycle.push_back(i);

    vector<pair<float,float>> coordinates = myWorld.getCoordinates();
    Agent anAgent(startCycle, coordinates);

    // ------- myWorld.saveCyclePlot cannot be called twice for some reasons ------
    // ------- Uncomment parts taht you like to see --------------------
//    vector<int> resultCycle_simple = anAgent.simpleHillClimb();
//    myWorld.saveCyclePlot(resultCycle_simple, "./test_simple.png");
    vector<int>resultCycle_steepest = anAgent.steepestAscendHillClimb();
    myWorld.saveCyclePlot(resultCycle_steepest, "./test_steepest.png");
    //TODO
    //Perform hill climbing here
    //Evaluate runtimes and results



    return 0;
}
