#pragma once
 
#include "stdafx.h"

std::vector<double> lin_space(double from, double to, int num_points);
double sum(const std::vector<double>& v);
double mean(const std::vector<double>& v);
double standard_deviation(const std::vector<double>& v, bool population = 0);
double min(const std::vector<double>& v);
double max(const std::vector<double>& v);
double prctile(const std::vector<double>& v, double percentage);
std::vector<double> sort(const std::vector<double>& v);
std::vector<double> rand_uniform(int n);
std::vector<double> rand_n(int n);
void rng(const std::string& description);
double normcdf(double x);
double norminv(double x); 


