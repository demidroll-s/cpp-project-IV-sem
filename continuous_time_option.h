#pragma once
 
#include "stdafx.h"
#include "priceable.h"

class Continuous_time_option:
    public Priceable
{
public:
    virtual ~Continuous_time_option() {};
    virtual double get_maturity() const = 0;
    virtual double payoff(const std::vector<double>& stock_prices) const = 0;
    virtual bool is_path_dependent() const = 0;
};
