// Written in May 2021 by Brenton Horne
#include <ODE.h>

/**
 * Returns the right-hand side of our ODE (currently the Rossler system).
 * 
 * @param t        A double pertaining to the value of time in our system.
 * @param X        An array of values of the dependent variables for our ODE.
 * @param params   An array of parameter values (as doubles) for our ODE.
 * @return         Vector of dX/dt values.
 */
vector<double> ODE(double t, vector<double> X, vector<double> params) {
    // Dependent variables
    double x = X[0];
    double y = X[1];
    double z = X[2];

    // Parameters
    double a = params[0];
    double b = params[1];
    double c = params[2];

    // dX/dt
    vector<double> dX {
        - y - z,        // dx/dt
        x + a * y,      // dy/dt
        b + z * (x-c)   // dz/dt
    };

    return dX;
}

/**
 * Main function, takes N (number of steps), tol and tf as user inputs and 
 * applies Euler's, Modified Euler's and the Runge-Kutta fourth order method to
 * solving the ODE: dX/dt = ODE(t, f, params)
 * with the initial condition X(t[0]) = X0, then writes the solution to a CSV
 * file and uses a Python script to plot the results.
 */
int main() {
    // Initialize variables
    int prec = 15;
    double t0 = 0.0; // Pretty normal to assume we start at t=0
    // Take input of N, tf and tol
    int N = getN();
    double tf = getTf();
    double tol = getTol();

    // Initialize relevant vectors
    vector<double> X0 {
        -0.1,
        0.5,
        -0.6
    };

    // Initialize params
    vector<double> params {
        0.1,
        0.1,
        14  
    };
    vector<string> headings {
        "t",
        "x",
        "y",
        "z"
    };

    // Write to tolerance file
    writeTol(tol);

    // Solve the problem using four different methods and plot the result
    solveProblem(ODE, X0, t0, tf, tol, N, prec, params, "Rossler", headings, 
    "3DPlots.py");
}