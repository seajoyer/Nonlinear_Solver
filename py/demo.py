from nonlinear_solver import Bisection, Newton

def main():

    def f(x: float) -> float:
        return x**5 - 7*x**3 - 3*x - 2

    tolerances = [1e-3, 1e-6, 1e-9]

    print("Solving x^5 - 7x^3 - 3x - 2 = 0 on interval [0, 10]")
    print("\nBisection method:")
    print("-" * 60)
    for tol in tolerances:
        bisection = Bisection(verbose=False)
        try:
            root = bisection.solve(f, 0, 10, tol=tol)
            print(f"ε = {tol:.0e}:")
            print(f"  Root = {root:.10f}")
            print(f"  f(root) = {f(root):.10f}")
            print(f"  Iterations: {bisection.iterations}")
        except Exception as e:
            print(f"Error: {e}")

    print("\nNewton's method:")
    print("-" * 60)
    for tol in tolerances:
        newton = Newton(verbose=False)
        try:
            root = newton.solve(f, x0=1.0, tol=tol)
            print(f"ε = {tol:.0e}:")
            print(f"  Root = {root:.10f}")
            print(f"  f(root) = {f(root):.10f}")
            print(f"  Iterations: {newton.iterations}")
        except Exception as e:
            print(f"Error: {e}")

if __name__ == "__main__":
    main()
