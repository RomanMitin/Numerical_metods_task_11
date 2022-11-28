#pragma once
#include "State.hpp"
#include <iostream>

void print_refence(std::ostream& out, const state_t& state);

void print_steps(std::ostream& out, const std::vector<step_info_t>& steps);