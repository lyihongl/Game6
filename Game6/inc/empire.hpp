#pragma once
#include <memory>
#include "economy.hpp"

class Empire{
    int32_t population;
    double money;

    const unsigned int foodOverhead;
    std::unique_ptr<Economy> economy;

    public:
    Empire();
    Empire(const Empire&) = delete;
    Empire operator=(const Empire&) = delete;
    Empire(Empire&&);
    ~Empire();
    void simulate(unsigned long long);
};