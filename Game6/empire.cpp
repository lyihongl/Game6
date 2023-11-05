#include "inc/empire.hpp"
#include "inc/economy.hpp"
// #include "inc/constants.hpp"

#include <iostream>
#include <vector>

Empire::Empire() : foodOverhead(50) {
    economy = std::make_unique<Economy>();
    population = 10;
    money = 10;
}

void Empire::simulate(unsigned long long ticks) {
    // std::vector<Constants::ResourceIndex> assignedJobs;
    std::unordered_map<std::string, uint32_t> peopleAllocation;

    if (economy->resources["food"] < foodOverhead * population) {
        uint32_t foodPeople = population * 0.8;
        uint32_t rest = population - foodPeople;
        peopleAllocation["food"] = foodPeople;
        while (rest > 0) {
            for (auto &it : economy->resources) {
                if (it.first == "food") continue;

                peopleAllocation[it.first]++;
                rest--;
                if (rest == 0) break;
            }
            if (rest == 0) break;
        }
    } else {
        uint32_t rest = population;
        while (rest > 0) {
            for (auto &it : economy->resources) {
                peopleAllocation[it.first]++;
                rest--;
                if (rest == 0) break;
            }
            if (rest == 0) break;
        }
    }

    if (ticks % 240 == 0) {
        economy->produce(peopleAllocation);
        economy->print();
    }
}

Empire::~Empire() {
}