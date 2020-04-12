#include <iostream>
#include <string.h>
#include <math.h>
#include <memory>

#include "extra_math.h"
#include "testing.h"

using namespace std;

class Black_Scholes_model
{
public:
    double stock_price;
    double volatility;
    double risk_free_rate;
    double date;

    Black_Scholes_model();
    explicit Black_Scholes_model(double stock_price);
};

Black_Scholes_model::Black_Scholes_model():
    stock_price(0.05),
    volatility(0.1),
    risk_free_rate(100.0),
    date(2.0) {}



class Call_option
{
public:
    double strike;
    double maturity;

    Call_option();
    Call_option(double strike, double majurity);

    double payoff(double stock_at_maturity) const;
    double price(const Black_Scholes_model& bsm) const;
};

Call_option::Call_option():
    strike(0.0),
    maturity(0.0) {}

Call_option::Call_option(double strike, double majurity):
    strike(strike),
    maturity(maturity) {}

double Call_option::payoff(double stock_at_maturity) const
{
    if(stock_at_maturity > strike)
        return stock_at_maturity - strike;
    else
        return 0;
}

double Call_option::price(const Black_Scholes_model& bsm) const
{
    double S = bsm.stock_price;
    double K = strike;
    double sigma = bsm.volatility;
    double r = bsm.risk_free_rate;
    double T = maturity - bsm.date;

    double numerator = log(S/K) + ( r + sigma * sigma * 0.5) * T;
    double denominator = sigma * sqrt(T);
    double d1 = numerator/denominator;
    double d2 = d1 - denominator;
    return S * normcdf(d1) - exp(-r * T) * K * normcdf(d2);
}

static void test_call_option_on_price()
{
    Call_option call_option;
    call_option.strike = 105.0;
    call_option.maturity = 2.0;
    
    Black_Scholes_model bsm;
    bsm.date = 1.0;
    bsm.volatility = 0.1;
    bsm.risk_free_rate = 0.05;
    bsm.stock_price = 100.0;

    double price = call_option.price(bsm);
    ASSERT_APPROX_EQUAL(price, 4.046, 0.01);
}

/////////////////////////////////////

class HedgingSimulator
{
private:
    std:: shared_ptr <Call_option>  to_hedge;
    std:: shared_ptr <Black_Scholes_model> simulation_model;
    std:: shared_ptr <Black_Scholes_model> pricing_model;
    int n_steps;
    void set_to_hedge (std::shared_ptr <Call_option> to_hedge)
    {
        this->to_hedge = to_hedge;
    }
};


