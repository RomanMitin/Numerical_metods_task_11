#pragma once
#include <cinttypes>
#include <vector>
#include <valarray>

constexpr int metod_order = 3;

enum class error_control_t
{
	No, Up, Up_and_Down
};

struct input_t
{
	double a, b;
	std::valarray<double> u0;

	double h0;

	uint64_t N_max;
	
	error_control_t error_control;
	double e_down, e_up, e_gr;
};

struct reference_t
{
	input_t input;

	uint64_t N;
	double step_left;
	//std::valarray<double> E_max;
	std::pair<double, double> S_max;
	std::pair<double, double> S_min{ 0,std::numeric_limits<double>::max() };

	uint64_t step_grow, step_decrease;

	std::pair<double, double> h_max;
	std::pair<double, double> h_min{ 0,std::numeric_limits<double>::max() };
};

struct step_info_t
{
	double h, t;
	std::valarray<double> v;
	double S;
	std::valarray<double> v_fin;

	//std::valarray<double> u;
	//double E;

	uint64_t step_grow, step_decrease;
};

struct state_t
{
	reference_t reference;

	std::vector<step_info_t> step_info_vec;
};