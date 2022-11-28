#pragma once
#include <assert.h>
#include <numeric>
#include "State.hpp"

inline double abs(std::valarray<double> vec)
{
	double result = 0;
	for (int i = 0; i < vec.size(); i++)
	{
		result = std::max(result, std::abs(vec[i]));
	}

	return result;
}

template <typename metod_t>
void calc(metod_t metod, state_t& state)
{
	input_t& input = state.reference.input;
	double t = input.a;
	double b = input.b;

	bool up_control = false;
	bool down_control = false;

	double e_up = std::numeric_limits <double>::max();
	if (input.error_control != error_control_t::No)
	{
		up_control = true;
		e_up = input.e_up;
	}

	double e_down = 0;
	if (input.error_control == error_control_t::Up_and_Down)
	{
		down_control = true;
		e_down = input.e_down;
	}

	double e_gr = input.e_gr;

	double h = input.h0;

	uint64_t max_step = input.N_max;

	std::valarray<double> v = input.u0;
	std::valarray<double> v_fin;

	assert(v.size() == 2);

	reference_t& reference = state.reference;
	
	std::pair<double, double> h_max(h, 0), h_min(h, 0);
	
	uint64_t step_count = 0;

	uint64_t step_dec_total = 0, step_grow_total = 0;

	std::pair<double, double> S_max(0, 0), S_min(0, 0);

	std::vector<step_info_t>& steps = state.step_info_vec;
	steps.reserve(std::min(max_step, 100'000ull));
	step_info_t step;
	
	step.h = h;
	step.v = v;
	step.v_fin = v;
	step.t = t;
	step.S = step.step_decrease = step.step_grow = 0;

	steps.push_back(step);

	std::valarray<double> S(2);
	bool resting_friction_flag = false;

	while (std::abs(b - t) >= e_gr && step_count < max_step && t <= b && !resting_friction_flag)
	{
		h = std::min((b - t) / 2.0, h);

		uint32_t step_dec = 0, step_grow = 0;
		std::valarray<double> tmp_v = v;

		try
		{
			v = metod(t, h, tmp_v, S);

			if (up_control)
			{
				while (abs(S) > e_up)
				{
					h /= 2;
					step_dec++;

					v = metod(t, h, tmp_v, S);
				}
			}

			if (down_control)
			{
				if (abs(S) < e_down)
				{
					step_grow++;
					h *= 2;
				}
			}

			t += h;

			if (reference.S_min.second > abs(S))
			{
				reference.S_min.second = abs(S);
				reference.S_min.first = t;
			}

			if (reference.S_max.second < abs(S))
			{
				reference.S_max.second = abs(S);
				reference.S_max.first = t;
			}

			if (reference.h_max.second < h)
			{
				reference.h_max.second = h;
				reference.h_max.first = t;
			}

			if (reference.h_min.second > h)
			{
				reference.h_min.second = h;
				reference.h_min.first = t;
			}
		}
		catch(int )
		{
			v[1] = 0;
			S[1] = 0;
			resting_friction_flag = true;
		}

		
		steps.back().h = h;
		step.t = t;
		step.v = v;
		step.S = abs(S);
		//v += S * (1ull << metod_order);
		step.v_fin = v;

		steps.back().step_decrease = step_dec;
		steps.back().step_grow = step_grow;

		steps.push_back(step);

		step_grow_total += step_grow;
		step_dec_total += step_dec;

		step_count++;
	}

	steps.back().h = 0;
	reference.N = step_count;
	reference.step_left = b - t;
	reference.step_decrease = step_dec_total;
	reference.step_grow = step_grow_total;
}