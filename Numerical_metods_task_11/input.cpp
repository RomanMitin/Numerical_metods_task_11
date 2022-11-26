#include "input.hpp"
#include <cmath>
#include <string>
#include <iostream>
#include "json.hpp"

using namespace nlohmann;

void from_json(const json& j, input_t& input)
{
	input.a = j.at("a");
	input.b = j.at("b");
	input.h0 = j.at("h0");

	if (input.h0 < 0)
	{
		std::cerr << "Step cant be less zero\n";
		exit(-1);
	}

	input.u0.resize(2);

	input.u0[0] = j.at("x");
	input.u0[1] = j.at("v");

	input.N_max = j.at("max_step");

	std::string err_control = j.at("error_control");
	if (err_control == "No")
	{
		input.error_control = error_control_t::No;
	}
	else
		if (err_control == "Up")
		{
			input.error_control = error_control_t::Up;
			input.e_up = j.at("e_up");
		}
		else
		{
			if (err_control == "Up_and_Down")
			{
				input.error_control = error_control_t::Up_and_Down;
				input.e_up = j.at("e_up");
				input.e_gr = j.at("e_gr");

				try
				{
					input.e_down = j.at("e_down");
					input.e_down = j.at("e_down");
				}
				catch (json::exception& exp)
				{
					input.e_down = input.e_up / (1ull << (metod_order + 1));
				}
			}
			else
			{
				std::cerr << "Wrong control parameter\n";
				exit(11);
			}
		}
}

void get_input(nlohmann::json& input_file, input_t& input)
{
	input = input_file.at("metod_param");
}

void from_json(const json& j, system_t& system)
{
	system.k = j.at("k");
	system.f = j.at("f");
	system.m = j.at("m");
	system.f_atr = j.at("f*");
	system.eps_rest = j.at("resting_friction_eps");

	if (system.k < 0 || system.f < 0 || system.m < 0 || system.f_atr < 0 || system.eps_rest < 0)
	{
		std::cerr << "System parametr cant be negative\n";
		exit(-1);
	}

	if (system.f >= system.f_atr)
	{
		std::cerr << "f cant be less f*\n";
		exit(-1);
	}
}


void get_system_param(nlohmann::json& input, system_t& system)
{
	system = input.at("system_param");
}
