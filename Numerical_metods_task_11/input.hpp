#pragma once
#include "json.hpp"
#include "State.hpp"
#include "system.hpp"


void get_input(nlohmann::json& input_file, input_t& input);

void get_system_param(nlohmann::json& input, system_t& system);