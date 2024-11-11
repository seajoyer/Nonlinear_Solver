from typing import Callable
from .exceptions import InvalidIntervalError

def check_interval(f: Callable[[float], float], a: float, b: float) -> None:
    """
    Check if the function changes sign on the interval [a, b]

    Args:
        f: Function to evaluate
        a: Left endpoint
        b: Right endpoint

    Raises:
        InvalidIntervalError: If function doesn't change sign on the interval
    """
    if f(a) * f(b) >= 0:
        raise InvalidIntervalError(
            f"Function must have different signs at interval endpoints: f({a})={f(a)}, f({b})={f(b)}"
        )

def derivative(f: Callable[[float], float], x: float, h: float = 1e-7) -> float:
    """
    Calculate numerical derivative using central difference

    Args:
        f: Function to differentiate
        x: Point at which to calculate derivative
        h: Step size

    Returns:
        Approximate derivative value
    """
    return (f(x + h) - f(x - h)) / (2 * h)
