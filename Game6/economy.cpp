#include "inc/economy.hpp"
#include "inc/constants.hpp"

#include <iostream>
#include <vector>

using namespace Constants;

Economy::Economy() {
    for(auto &it : ResourcesMetadata) {
        resources[it.getName()] = 0;
    }
    resources[getResourceName(ResourceIndex::WOOD)] = 20;
}

Economy::Economy(Economy &e){

}

Economy::Economy(Economy &&e){

}

Economy Economy::operator=(Economy &e){
    return {};
}

Economy::~Economy(){}

void Economy::produce(std::unordered_map<std::string, uint32_t> &people) {
    for(auto &it : people) {
        resources[it.first] += it.second*2;
    }
}

void Economy::print() const {
    std::cout<<"== economy ==\n";
    for(const auto &it : resources) {
        std::cout<<it.first<<": "<<it.second<<"\n";
    }
    std::cout<<std::endl;
}