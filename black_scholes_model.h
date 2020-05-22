#pragma once

#include "stdafx.h"

class Black_Scholes_model
{
public:
    double drift;
    double stock_price;
    double volatility;
    double risk_free_rate;
    double date;
    Black_Scholes_model();
    Black_Scholes_model(double drift, double stock_price, double volatility, double risk_free_rate, double date);
    std::vector<double> generate_price_path(double to_date, int n_steps) const;
    std::vector<double> generate_risk_neutral_price_path(double to_date, int n_steps) const;
private:
    std::vector<double> generate_price_path(double to_date, int n_steps, double drift) const;
};

void test_bsm();

