#ifndef AGENT_HPP
#define AGENT_HPP

#include <vector>
#include "world.hpp"

using namespace std;

class Agent {
    public:
        Agent(vector<int> startCycle, vector<pair<float,float>> coordinates);
        ~Agent();

        vector<int> simpleHillClimb();
        vector<int> steepestAscendHillClimb();
        float findCost(vector<int> cycle);

    private:
        World* worldPtr;
        vector<pair<float,float>> coordinates;
        vector<int> startCycle;
        vector<int> currentCycle;
        vector<int> resultCycle;
        float resultCost;
        float currentCost;
        bool break_outer_loop;
        bool find_local_min;

};
#endif
