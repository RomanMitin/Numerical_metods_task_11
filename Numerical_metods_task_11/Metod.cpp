#include "Metod.hpp"
#include "System.hpp"
#include "State.hpp"

extern system_t system_var;


std::valarray<double> func(double t,const std::valarray<double>& v)
{
	return system_var.func(v);
}

std::valarray<double> euler(double t, double h, std::valarray<double> v, std::valarray<double>& S)
{
	return v + h * func(t, v);
}

std::valarray<double> runge_khuta_2_order(double t, double h, std::valarray<double> v, std::valarray<double>& S)
{
	auto k1 = func(t, v);
	auto k2 = func(t + h, v + h * k1);

	auto v1 = v + h / 2 * (k1 + k2);

	std::valarray<double> v2;
	h /= 2;

	for (int i = 0; i < 2; i++)
	{
		k1 = func(t, v);
		k2 = func(t + h, v + h * k1);

		v2 = v + h / 2 * (k1 + k2);
		v = v2;
	}

	S = (v2 - v1) / ((1ull << metod_order) - 1);

	return v1;
}

std::valarray<double> runge_khuta_3_order(double t, double h, std::valarray<double> v, std::valarray<double>& S)
{
	auto k1 = func(t, v);
	auto k2 = func(t + h / 3.0, v + h / 3.0 * k1);
	auto k3 = func(t + 2.0 * h / 3.0, v + 2.0 * h / 3.0 * k2);

	std::valarray<double> v1 = v + h * (k1 / 4.0 + 3.0 / 4.0 * k3);

	std::valarray<double> v2;
	h /= 2.0;

	for (int i = 0; i < 2; i++)
	{
		k1 = func(t, v);
		k2 = func(t + h / 3.0, v + h / 3.0 * k1);
		k3 = func(t + 2.0 * h / 3.0, v + 2.0 * h / 3.0 * k2);

		v2 = v + h * (k1 / 4.0 + 3.0 / 4.0 * k3);
		v = v2;
		t += h;
	}

	S = (v2 - v1) / ((1ull << metod_order) - 1);

	return v1;
}

std::valarray<double> runge_khuta_mersona(double t, double h, std::valarray<double> v, std::valarray<double>& S)
{
	std::valarray<double> k1 = func(t, v);
	std::valarray<double> k2 = func(t + h / 3, v + h / 3 * k1);
	std::valarray<double> k3 = func(t + h / 3, v + h / 6 * k1 + h / 6 * k2);
	std::valarray<double> k4 = func(t + h / 2, v + h / 8 * k1 + 3 * h / 8 * k3);
	std::valarray<double> k5 = func(t + h, v + h / 2 * k1 - 3 * h / 2 * k3 + 2 * h * k4);

	S = h / 30 * (-2 * k1 + 9 * k3 - 8 * k4 + k5);
	v += h / 6 * (k1 + 4 * k4 + k5);
	//v += h / 10 * (k1 + 3 * k3 + 4 * k4 + 2 * k5);

	return v;
}