#include "../include/nonlinear_solver/utils.hpp"
#include "../include/nonlinear_solver/exceptions.hpp"
#include <sstream>

namespace nonlinear_solver {

void check_interval(const std::function<double(double)>& f, double a, double b) {
    if (f(a) * f(b) >= 0) {
        std::ostringstream oss;
        oss << "Function must have different signs at interval endpoints: "
            << "f(" << a << ")=" << f(a) << ", f(" << b << ")=" << f(b);
        throw InvalidIntervalError(oss.str());
    }
}

double derivative(const std::function<double(double)>& f, double x, double h) {
    return (f(x + h) - f(x - h)) / (2 * h);
}

}
