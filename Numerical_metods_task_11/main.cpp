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

	std::string output_f_name = "output.csv";

	if (argc >= 3)
	{
		output_f_name = argv[2];
	}

	std::ofstream out(output_f_name);

	print_refence(out, state);

	print_steps(out, state.step_info_vec);
	
	out.close();

	system((std::string("start excel ") + output_f_name).c_str());

	while (1);

	return 0;
}