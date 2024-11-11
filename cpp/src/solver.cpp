#include "../include/nonlinear_solver/solver.hpp"
#include "../include/nonlinear_solver/utils.hpp"
#include <iostream>
#include <cmath>

namespace nonlinear_solver {

NonlinearSolver::NonlinearSolver(size_t max_iter, bool verbose)
    : max_iter_(max_iter), verbose_(verbose), iterations_(0) {}

double Bisection::solve(const std::function<double(double)>& f,
                       double a, double b,
                       double tol) {
    check_interval(f, a, b);

    iterations_ = 0;
    double fa = f(a);

    while ((b - a) / 2 > tol) {
        iterations_++;
        if (iterations_ > max_iter_) {
            throw ConvergenceError(
                "Failed to converge in " + std::to_string(max_iter_) + " iterations"
            );
        }

        double c = (a + b) / 2;
        double fc = f(c);

        if (verbose_) {
            std::cout << "Iteration " << iterations_
                     << ": x = " << c
                     << ", f(x) = " << fc << std::endl;
        }

        if (fc == 0) {
            return c;
        } else if (fc * fa < 0) {
            b = c;
        } else {
            a = c;
            fa = fc;
        }
    }

    return (a + b) / 2;
}

double Newton::solve(const std::function<double(double)>& f,
                    double x0,
                    double tol,
                    double h) {
    double x = x0;
    iterations_ = 0;

    while (true) {
        iterations_++;
        if (iterations_ > max_iter_) {
            throw ConvergenceError(
                "Failed to converge in " + std::to_string(max_iter_) + " iterations"
            );
        }

        double fx = f(x);
        if (std::abs(fx) < tol) {
            return x;
        }

        double df = derivative(f, x, h);
        if (df == 0) {
            throw ConvergenceError("Derivative is zero");
        }

        double x_new = x - fx / df;

        if (verbose_) {
            std::cout << "Iteration " << iterations_
                     << ": x = " << x_new
                     << ", f(x) = " << fx << std::endl;
        }

        if (std::abs(x_new - x) < tol) {
            return x_new;
        }

        x = x_new;
    }
}

}
