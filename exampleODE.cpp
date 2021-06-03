// Created using newODE.cpp
#include <ODE.h>

/**
 * Returns the right-hand side of our ODE (currently the example system)
 *
 * @param t        A double pertaining to the value of time in our system.
 * @param X        An array of values of the dependent variables for our ODE.
 * @param params   An array of parameter values (as doubles) for our ODE.
 * @return         Vector of dX/dt values.
 */
vector<double> ODE(double t, vector<double> X, vector<double> params) {
    double u = X[0];
    double du = X[1];
    
    vector<double> dX {
    	du,
    	-u*cos(u)
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
    int prec = 15;
    double t0 = 0;
    int N = getN();
    double tf = getTf();
    double tol = getTol();
    // Initialize relevant vectors
    vector<double> X0 {        
        0.0,
        1.0
    };
    // Initialize params
    vector<double> params {
        0
    };
    vector<string> headings {
        "t",
        "u",
        "du"
    };
 
    // Write tolerance to file
    writeTol(tol);
 
    // Solve the problem using four different methods and plot the result
    solveProblem(ODE, X0, t0, tf, tol, N, prec, params, "example", headings, "2DPlots.py");
}
