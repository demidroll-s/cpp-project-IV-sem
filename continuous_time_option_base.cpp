#include "continuous_time_option_base.h"
#include "monte_carlo.h"
#include "call_option.h"

#include "matlib.h"
#include "testing.h"

double Continuous_time_option_base::price(const Black_Scholes_model& model) const
{
    Monte_Carlo_pricer pricer;
    return pricer.price(*this, model);
}