#pragma once
#include <valarray>

struct system_t
{
	double k, f, m, f_atr;

	double eps_rest;

	std::valarray<double> func(const std::valarray<double>& u);
};