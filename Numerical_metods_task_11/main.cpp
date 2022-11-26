#include <iostream>
#include <fstream>
#include <string>
#include "Metod.hpp"
#include "input.hpp"
#include "Output.hpp"
#include "json.hpp"
#include "Calc.hpp"

using namespace nlohmann;

extern system_t system_var;

int main(int argc, char* argv[])
{
	std::string input_f_name = "input.json";

	if (argc < 2)
	{
		//std::cerr << "Warning, missing input file\n";
	}
	else
	{
		input_f_name = argv[1];
	}

	std::ifstream in_file(input_f_name);

	if (!in_file.is_open())
	{
		std::cerr << "Cant open file " << input_f_name << '\n';
		exit(1);
	}

	json input_json = json::parse(in_file);

	in_file.close();

	state_t state;
	get_input(input_json, state.reference.input);

	get_system_param(input_json, system_var);

	calc(runge_khuta_3_order, state);

	print_refence(state);


	print_steps(state.step_info_vec);

	return 0;
}