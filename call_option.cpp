#include "call_option.h"

#include "matlib.h"

using namespace std;

double Call_option::payoff(double stock_at_maturity) const
{
    if(stock_at_maturity > get_strike())
        return stock_at_maturity - get_strike();
    else
        return 0;
}

double Call_option::price(const Black_Scholes_model& bsm) const
{
    double S = bsm.stock_price;
    double K = get_strike();
    double sigma = bsm.volatility;
    double r = bsm.risk_free_rate;
    double T = get_maturity() - bsm.date;
    double numerator = log(S/K) + ( r + sigma * sigma * 0.5) * T;
    double denominator = sigma * sqrt(T);
    double d1 = numerator / denominator;
    double d2 = d1 - denominator;
    return S * normcdf(d1) - exp((-1) * r * T) * K * normcdf(d2);
}

double Call_option::delta(const Black_Scholes_model& bsm) const
{
    double S = bsm.stock_price;
    double K = get_strike();
    double sigma = bsm.volatility;
    double r = bsm.risk_free_rate;
    double T = get_maturity() - bsm.date;

    double numerator = log (S / K)+(r + sigma * sigma *0.5) * T;
    double denominator = sigma * sqrt(T);
    double d1 = numerator / denominator;
    return normcdf(d1);
}