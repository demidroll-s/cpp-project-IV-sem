#pragma once

#include "black_scholes_model.h"
#include "call_option.h"
#include "stdafx.h"

class Hedging_simulator
{
private:
    /* Option for hedging */
    std::shared_ptr <Call_option>  to_hedge;
    /* Model to simulate stock price */
    std::shared_ptr <Black_Scholes_model> simulation_model;
    /* Model to calculate deltas and prices */
    std::shared_ptr <Black_Scholes_model> pricing_model;
    /* Number of iterations for hedging */
    int n_steps;
public:
    void set_to_hedge(std::shared_ptr <Call_option> to_hedge)
    {
        this->to_hedge = to_hedge;
    }
    void set_simulation_model(std::shared_ptr <Black_Scholes_model> model)
    {
        this->simulation_model = model;
    }
    void set_pricing_model(std::shared_ptr <Black_Scholes_model> model)
    {
        this->pricing_model = model;
    }
    void set_n_steps(int n_steps)
    {
        this->n_steps = n_steps;
    }
    Hedging_simulator();
    Hedging_simulator(double maturity, Black_Scholes_model model_, int n_steps_);
    std::vector <double> run_simulations(int n_simulations) const;
    double run_simulation() const;
    double choose_charge(double stock_price) const;
    double select_stock_quantity(double date, double stock_price) const;
};

void test_hedging();

