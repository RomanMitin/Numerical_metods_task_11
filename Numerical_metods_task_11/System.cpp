#include "System.hpp"
#include <cassert>
#include <iostream>

system_t system_var;

double sign(double n)
{

	if (n > 0.0)
		return 1.0;
	else
		return -1.0;
}

constexpr double g = 9.81;

// check y == 0
std::valarray<double> system_t::func(const std::valarray<double>& u)
{
	assert(u.size() == 2);

	double x = u[0];
	double v = u[1];

	std::valarray<double> res(2);
	res[0] = v;
	
	if (std::abs(v) < eps_rest)
	{
		if (std::abs(m * g * f_atr) >= std::abs(k * x))
		{
			res[1] = 0;
			throw 0;
		}
		else
			res[1] = -k / m * x + g * f_atr * sign(x);
	}
	else
	{
		res[1] = -g * f * sign(v) - k / m * x;
	}
	//std::cout << res[1] << '\t';
	//std::cout << res.size() << '\n';
	return res;
}
