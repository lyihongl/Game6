#pragma once
#include "resource.hpp"

#include <unordered_map>
#include <string>

class Economy {
    public:
    std::unordered_map<std::string, uint32_t> resources;

    Economy();   
    Economy(Economy&);
    Economy(Economy&&);
    Economy operator=(Economy&);
    ~Economy();
    void produce(std::unordered_map<std::string, uint32_t>&);
    void print() const;
};