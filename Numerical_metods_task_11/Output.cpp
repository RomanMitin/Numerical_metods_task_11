#include "Output.hpp"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <sstream>

constexpr int tab_size = 10;
constexpr int precision = 5;

//using namespace std;
auto setw(int count)
{
	return std::string(" ; ");
	//return std::setw(count);
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

void print_refence(std::ostream& out, const state_t& state)
{
	const reference_t& reference = state.reference;

	out << "------------------- REFERENCE -------------------\n";
	out << "TASK 11\n";
	out << "Done by Mitin Roman\n";
	out << "Runge-kutta 3 order method\n";

	out << "INPUT PARAM:\n";
	out << "t_0 = " << reference.input.a << ";\tx0 = " << reference.input.u0[0] << ";\tv0=" << reference.input.u0[1] << '\n';
	out << "b = " << reference.input.b << ";\te_gr = " << reference.input.e_gr << '\n';
	out << "h0 = " << reference.input.h0 << ";\tN_max = " << reference.input.N_max << '\n';
	out << "e = " << reference.input.e_up << ";\te_min = " << reference.input.e_down << "\n\n";


	out << "Calculation result:\n";
	out << "N = " << reference.N << '\n';
	out << "b - x_n = " << reference.step_left << '\n';
	out << "t_n = " << state.step_info_vec.back().t << ";\tx_n = " << state.step_info_vec.back().v[0]
		<< ";\tv0 = " << state.step_info_vec.back().v[1] << "\n\n";

	out << "max |S| " << reference.S_max.second << ";\t x = " << reference.S_max.first << '\n';
	out << "min |S| " << reference.S_min.second << ";\t x = " << reference.S_min.first << '\n';

	out << "Total step increase: " << reference.step_grow << '\n';
	out << "Total step decrease: " << reference.step_decrease << '\n';

	out << "max h = " << reference.h_max.second << ";\t x = " << reference.h_max.first << '\n';
	out << "min h = " << reference.h_min.second << ";\t x = " << reference.h_min.first << "\n\n";
}



void print_steps(std::ostream& out, const std::vector<step_info_t>& steps)
{
	out << "------------------- Result table -------------------\n";

	out << std::setprecision(precision);

	out << "n" << setw(tab_size) << "h" << setw(tab_size);
	out << "t" << setw(tab_size) << "x" << setw(tab_size);
	out << "v" << setw(tab_size) << "S" << setw(tab_size);
	out << "x_fin" << setw(tab_size) << "v_fin";
	out <<  setw(tab_size) << "s_dec" << setw(tab_size) << "s_grow" << '\n';

	for (int i = 0; i < steps.size(); i++)
	{
		out << i << setw(tab_size) << steps[i].h << setw(tab_size) << steps[i].t << setw(tab_size) << steps[i].v;
		out << steps[i].S << setw(tab_size) << steps[i].v_fin;
		out << steps[i].step_decrease << setw(tab_size) << steps[i].step_grow << '\n';
	}

	out << '\n';
}