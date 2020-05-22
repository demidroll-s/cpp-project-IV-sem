#pragma once
 
#include "stdafx.h"
#include "black_scholes_model.h"
#include "path_independent_option.h"

class Call_option:
    public Path_independent_option
{
public:
    double payoff(double stock_at_maturity) const;
    double price(const Black_Scholes_model& bsm) const;
    double delta(const Black_Scholes_model& bsm) const;
};

