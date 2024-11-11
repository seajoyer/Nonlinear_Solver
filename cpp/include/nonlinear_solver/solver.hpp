#pragma once

#include <functional>
#include "exceptions.hpp"

namespace nonlinear_solver {

class NonlinearSolver {
public:
    NonlinearSolver(size_t max_iter = 1000, bool verbose = false);
    virtual ~NonlinearSolver() = default;

    virtual double solve(const std::function<double(double)>& f,
                        double tol = 1e-6) = 0;

protected:
    size_t max_iter_;
    bool verbose_;
    size_t iterations_;
};

class Bisection : public NonlinearSolver {
public:
    using NonlinearSolver::NonlinearSolver;

    double solve(const std::function<double(double)>& f,
                double a, double b,
                double tol = 1e-6);

    double solve(const std::function<double(double)>& f,
                double tol = 1e-6) override {
        throw NonlinearSolverError("Bisection method requires interval bounds");
    }
};

class Newton : public NonlinearSolver {
public:
    using NonlinearSolver::NonlinearSolver;

    double solve(const std::function<double(double)>& f,
                double x0,
                double tol = 1e-6,
                double h = 1e-7);

    double solve(const std::function<double(double)>& f,
                double tol = 1e-6) override {
        throw NonlinearSolverError("Newton's method requires initial guess");
    }
};

}
