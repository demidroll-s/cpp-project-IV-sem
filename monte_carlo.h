#pragma once
 
#include "stdafx.h"
#include "black_scholes_model.h"
#include "continuous_time_option.h"

class Monte_Carlo_pricer
{
public:
    Monte_Carlo_pricer();
    int n_scenarios;
    int n_steps;
    double price(const Continuous_time_option& option, const Black_Scholes_model& model);
};

