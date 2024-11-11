from typing import Callable
from .exceptions import ConvergenceError
from .utils import check_interval, derivative

class NonlinearSolver:
    """Base class for nonlinear equation solvers"""

    def __init__(self, max_iter: int = 1000, verbose: bool = False):
        """
        Initialize solver

        Args:
            max_iter: Maximum number of iterations
            verbose: If True, print iteration info
        """
        self.max_iter = max_iter
        self.verbose = verbose
        self.iterations = 0

    def solve(self, f: Callable[[float], float], *args, **kwargs) -> float:
        """
        Solve nonlinear equation

        Args:
            f: Function to find root of

        Returns:
            Approximate root value
        """
        raise NotImplementedError("Subclasses must implement solve method")

class Bisection(NonlinearSolver):
    """Bisection method solver"""

    def solve(self, f: Callable[[float], float],
             a: float, b: float,
             tol: float = 1e-6) -> float:
        """
        Find root using bisection method

        Args:
            f: Function to find root of
            a: Left endpoint of interval
            b: Right endpoint of interval
            tol: Solution tolerance

        Returns:
            Approximate root value
        """
        check_interval(f, a, b)

        self.iterations = 0
        fa = f(a)

        while (b - a) / 2 > tol:
            self.iterations += 1
            if self.iterations > self.max_iter:
                raise ConvergenceError(
                    f"Failed to converge in {self.max_iter} iterations"
                )

            c = (a + b) / 2
            fc = f(c)

            if self.verbose:
                print(f"Iteration {self.iterations}: x = {c:.10f}, f(x) = {fc:.10f}")

            if fc == 0:
                return c
            elif fc * fa < 0:
                b = c
            else:
                a = c
                fa = fc

        return (a + b) / 2

class Newton(NonlinearSolver):
    """Newton's method solver"""

    def solve(self, f: Callable[[float], float],
             x0: float, tol: float = 1e-6,
             h: float = 1e-7) -> float:
        """
        Find root using Newton's method

        Args:
            f: Function to find root of
            x0: Initial guess
            tol: Solution tolerance
            h: Step size for derivative approximation

        Returns:
            Approximate root value
        """
        x = x0
        self.iterations = 0

        while True:
            self.iterations += 1
            if self.iterations > self.max_iter:
                raise ConvergenceError(
                    f"Failed to converge in {self.max_iter} iterations"
                )

            fx = f(x)
            if abs(fx) < tol:
                return x

            df = derivative(f, x, h)
            if df == 0:
                raise ConvergenceError("Derivative is zero")

            x_new = x - fx / df

            if self.verbose:
                print(f"Iteration {self.iterations}: x = {x_new:.10f}, f(x) = {fx:.10f}")

            if abs(x_new - x) < tol:
                return x_new

            x = x_new
