#pragma once
 
#include "stdafx.h"
#include "black_scholes_model.h"
#include "path_independent_option.h"

class Put_option:
    public Continuous_time_option_base
{
public:
    double payoff(const std::vector<double>& stock_prices) const;
    double price(const Black_Scholes_model& bsm) const;
    bool is_path_dependent() const
    {
        return false;
    };
};