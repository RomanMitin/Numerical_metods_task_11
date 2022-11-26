#pragma once
#include <algorithm>
#include <valarray>

std::valarray<double> euler(double t, double h, std::valarray<double> v, std::valarray<double>& S);

std::valarray<double> runge_khuta_2_order(double t, double h, std::valarray<double> v, std::valarray<double>& S);

std::valarray<double> runge_khuta_3_order(double t, double h, std::valarray<double> v, std::valarray<double>& S);

std::valarray<double> runge_khuta_mersona(double t, double h, std::valarray<double> v, std::valarray<double>& S);