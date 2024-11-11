class NonlinearSolverError(Exception):
    """Base exception class for nonlinear solver errors"""
    pass

class ConvergenceError(NonlinearSolverError):
    """Raised when the method fails to converge"""
    pass

class InvalidIntervalError(NonlinearSolverError):
    """Raised when the root is not bracketed in the given interval"""
    pass
