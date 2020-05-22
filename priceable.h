#pragma once
 
#include "black_scholes_model.h"

class Priceable
{
public:
    virtual double price(const Black_Scholes_model& model) const = 0;
};