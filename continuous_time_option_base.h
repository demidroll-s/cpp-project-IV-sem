#pragma once
 
#include "continuous_time_option.h"
#include "black_scholes_model.h"

class Continuous_time_option_base: 
    public Continuous_time_option
{
public:
    virtual ~Continuous_time_option_base() {}
 
    double get_maturity() const
    {
        return maturity;
    }
    void set_maturity(double maturity)
    {
        this->maturity = maturity;
    }
    double get_strike() const
    {
        return strike;
    }
    void set_strike(double strike)
    {
        this->strike = strike;
    }
    virtual double price(const Black_Scholes_model& model) const;
private:
    double maturity;
    double strike;
};
