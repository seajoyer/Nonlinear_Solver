#include "include/nonlinear_solver/solver.hpp"
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>

double f(double x) {
    return std::pow(x, 5) - 7 * std::pow(x, 3) - 3 * x - 2;
}

int main() {
    std::vector<double> tolerances = {1e-3, 1e-6, 1e-9};

    std::cout << "Solving x^5 - 7x^3 - 3x - 2 = 0 on interval [0, 10]\n\n";

    std::cout << "Bisection method:\n";
    std::cout << std::string(60, '-') << "\n";
    for (double tol : tolerances) {
        nonlinear_solver::Bisection bisection(1000, false);
        try {
            double root = bisection.solve(f, 0, 10, tol);
            std::cout << "ε = " << std::scientific << tol << ":\n";
            std::cout << std::fixed << std::setprecision(10);
            std::cout << "  Root = " << root << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    std::cout << "\nNewton's method:\n";
    std::cout << std::string(60, '-') << "\n";
    for (double tol : tolerances) {
        nonlinear_solver::Newton newton(1000, false);
        try {
            double root = newton.solve(f, 1.0, tol);
            std::cout << "ε = " << std::scientific << tol << ":\n";
            std::cout << std::fixed << std::setprecision(10);
            std::cout << "  Root = " << root << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
