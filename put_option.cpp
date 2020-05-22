#include "put_option.h"

#include "matlib.h"

double Put_option::payoff(const std::vector<double>& stock_prices) const
{
    double stock_at_maturity = stock_prices.back();
    if (stock_at_maturity < get_strike())
        return get_strike()-stock_at_maturity;
    else
        return 0.0;
}
 
double Put_option::price(const Black_Scholes_model& bsm) const
{
    double S = bsm.stock_price;
    double K = get_strike();
    double sigma = bsm.volatility;
    double r = bsm.risk_free_rate;
    double T = get_maturity() - bsm.date;
 
    double numerator = log(S/K) + (r + sigma * sigma * 0.5) *T;
    double denominator = sigma * sqrt(T);
    double d1 = numerator / denominator;
    double d2 = d1 - denominator;
    return -S * normcdf(-d1) + exp(-r * T) * K * normcdf(-d2);
}