#pragma once

#include <stdexcept>
#include <string>

namespace nonlinear_solver {

class NonlinearSolverError : public std::runtime_error {
public:
    explicit NonlinearSolverError(const std::string& message)
        : std::runtime_error(message) {}
};

class ConvergenceError : public NonlinearSolverError {
public:
    explicit ConvergenceError(const std::string& message)
        : NonlinearSolverError(message) {}
};

class InvalidIntervalError : public NonlinearSolverError {
public:
    explicit InvalidIntervalError(const std::string& message)
        : NonlinearSolverError(message) {}
};

}
