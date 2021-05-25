// Written in May 2021 by Brenton Horne
#include <ODE.h>

/**
 * Returns the right-hand side of our ODE (currently the simple pendulum).
 * 
 * @param t        A double pertaining to the value of time in our system.
 * @param X        An array of values of the dependent variables for our ODE.
 * @param params   An array of parameter values (as doubles) for our ODE.
 * @return         Vector of dX/dt values.
 */
vector<double> ODE(double t, vector<double> X, vector<double> params) {
    // Dependent variables
    double theta = X[0];
    double dtheta = X[1];

    // Parameters
    double g = params[0];
    double l = params[1];

    // dX/dt
    vector<double> dX(2);
    dX[0] = dtheta;
    dX[1] = -g/l * cos(theta);

    return dX;
}

/**
 * Main function, takes N (number of steps) and tf as user inputs and applies
 * Euler's, Modified Euler's and the Runge-Kutta fourth order method to solving
 * the ODE: dX/dt = ODE(t, f, params)
 * with the initial condition X(t[0]) = X0, then writes the solution to a CSV
 * file and uses a Python script to plot the results.
 */
int main() {
    // Initialize variables
    int prec = 15;
    double t0 = 0.0; // Pretty normal to assume we start at t=0
    // Take input of N and tf
    int N = getN();
    double tf = getTf();
    // Compute step size
    double tol = getTol();

    // Initialize relevant vectors
    vector<double> X0 {
        0.0,
        0.0
    };
    vector<double> params {
        9.8,
        1.0
    };

    // Write solution data to CSV file (easiest to import into Python)
    vector<string> headings {
        "t",
        "theta",
        "thetaDot"
    };

    // Solve the problem using four different methods and plot the result
    solveProblem(ODE, X0, t0, tf, tol, N, prec, params, "Simple pendulum", headings, "plotEx3SP.py");
}