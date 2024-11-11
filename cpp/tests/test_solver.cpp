#include <nonlinear_solver/solver.hpp>
#include <gtest/gtest.h>
#include <cmath>

using namespace nonlinear_solver;

// Simple function: x^2 - 2 = 0 (root at sqrt(2))
double f1(double x) {
    return x * x - 2;
}

TEST(BisectionTest, SimpleFunction) {
    Bisection solver;
    double root = solver.solve(f1, 1, 2, 1e-6);
    EXPECT_NEAR(f1(root), 0, 1e-6);
    EXPECT_NEAR(root, std::sqrt(2), 1e-6);
}

TEST(NewtonTest, SimpleFunction) {
    Newton solver;
    double root = solver.solve(f1, 1.5, 1e-6);
    EXPECT_NEAR(f1(root), 0, 1e-6);
    EXPECT_NEAR(root, std::sqrt(2), 1e-6);
}

// Function with no real roots: x^2 + 1 = 0
double f2(double x) {
    return x * x + 1;
}

TEST(BisectionTest, InvalidInterval) {
    Bisection solver;
    EXPECT_THROW(solver.solve(f2, -1, 1), InvalidIntervalError);
}

// Function with multiple asymptotes: tan(x)
double f3(double x) {
    return std::tan(x);
}

TEST(NewtonTest, ConvergenceFailure) {
    Newton solver(10);  // Small max_iter to force failure
    EXPECT_THROW(solver.solve(f3, 1.5), ConvergenceError);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
