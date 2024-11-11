#pragma once

#include <functional>

namespace nonlinear_solver {

// Check if function changes sign on interval [a, b]
void check_interval(const std::function<double(double)>& f, double a, double b);

// Calculate numerical derivative using central difference
double derivative(const std::function<double(double)>& f, double x, double h = 1e-7);

}
