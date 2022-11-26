#include "Output.hpp"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <sstream>

constexpr int tab_size = 10;
constexpr int precision = 3;

//using namespace std;
auto setw(int count)
{
	return std::setw(count);
}

std::ostream& operator<<(std::ostream& out, std::valarray<double> arr)
{
	assert(arr.size() == 2);

	for (int i = 0; i < arr.size(); i++)
	{
		out << arr[i] << setw(tab_size);
	}

	return out;
}

void print_refence(const state_t& state)
{
	const reference_t& reference = state.reference;

	std::cout << "------------------- REFERENCE -------------------\n";
	std::cout << "TASK 11\n";
	std::cout << "Runge-kutta 3 order method\n";

	std::cout << "INPUT PARAM:\n";
	std::cout << "t_0 = " << reference.input.a << ";\tx0 = " << reference.input.u0[0] << ";\tv0=" << reference.input.u0[1] << '\n';
	std::cout << "b = " << reference.input.b << ";\te_gr = " << reference.input.e_gr << '\n';
	std::cout << "h0 = " << reference.input.h0 << ";\tN_max = " << reference.input.N_max << '\n';
	std::cout << "e = " << reference.input.e_up << ";\te_min = " << reference.input.e_down << "\n\n";


	std::cout << "Calculation result:\n";
	std::cout << "N = " << reference.N << '\n';
	std::cout << "b - x_n = " << reference.step_left << '\n';
	std::cout << "t_n = " << state.step_info_vec.back().t << ";\tx_n = " << state.step_info_vec.back().v[0]
		<< ";\tv0=" << state.step_info_vec.back().v[1] << "\n\n";

	std::cout << "max |S| " << reference.S_max.second << ";\t x = " << reference.S_max.first << '\n';
	std::cout << "min |S| " << reference.S_min.second << ";\t x = " << reference.S_min.first << '\n';

	std::cout << "Total step increase: " << reference.step_grow << '\n';
	std::cout << "Total step decrease: " << reference.step_decrease << '\n';

	std::cout << "max h = " << reference.h_max.second << ";\t x = " << reference.h_max.first << '\n';
	std::cout << "min h = " << reference.h_min.second << ";\t x = " << reference.h_min.first << "\n\n";
}



void print_steps(const std::vector<step_info_t>& steps)
{
	std::cout << "------------------- Result table -------------------\n";

	std::cout << std::setprecision(precision);

	std::cout << "n" << setw(tab_size) << "h" << setw(tab_size);
	std::cout << "t" << setw(tab_size) << "x" << setw(tab_size);
	std::cout << "v" << setw(tab_size) << "S" << setw(tab_size);
	std::cout << "x_fin" << setw(tab_size) << "v_fin";
	std::cout <<  setw(tab_size) << "s_dec" << setw(tab_size) << "s_grow" << '\n';

	for (int i = 0; i < steps.size(); i++)
	{
		std::cout << i << setw(tab_size) << steps[i].h << setw(tab_size) << steps[i].t << setw(tab_size) << steps[i].v;
		std::cout << setw(tab_size) << steps[i].S << setw(tab_size) << steps[i].v_fin;
		std::cout << setw(tab_size) << steps[i].step_decrease << setw(tab_size) << steps[i].step_grow << '\n';
	}

	std::cout << '\n';
}