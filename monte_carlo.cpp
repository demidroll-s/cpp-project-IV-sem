#include "monte_carlo.h"

#include "matlib.h"
#include "call_option.h"

using namespace std;

Monte_Carlo_pricer::Monte_Carlo_pricer():
    n_scenarios(10000),
    n_steps(10) {}

double Monte_Carlo_pricer::price(const Continuous_time_option& option, const Black_Scholes_model& model)
{
    int n_steps = this->n_steps;
    if(!option.is_path_dependent())
        n_steps = 1;
    double total = 0.0;
    for (int i = 0; i < n_scenarios; i++)
    {
        vector<double> path = model.generate_risk_neutral_price_path(option.get_maturity(), n_steps);
        double payoff = option.payoff(path);
        total += payoff;
    }
    double mean = total / n_scenarios;
    double r = model.risk_free_rate;
    double T = option.get_maturity() - model.date;
    return exp(-r * T) * mean;
}