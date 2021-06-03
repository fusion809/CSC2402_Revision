// Created using newODE.cpp
#include <ODE.h>

/**
 * Returns the right-hand side of our ODE (currently the Hindmarsh-Rose model)
 *
 * @param t        A double pertaining to the value of time in our system.
 * @param X        An array of values of the dependent variables for our ODE.
 * @param params   An array of parameter values (as doubles) for our ODE.
 * @return         Vector of dX/dt values.
 */
vector<double> ODE(double t, vector<double> X, vector<double> params) {
    double x = X[0];
    double y = X[1];
    double z = X[2];
    
    double a = params[0];
    double b = params[1];
    double c = params[2];
    double d = params[3];
    double r = params[4];
    double s = params[5];
    double xR = params[6];
    double I = params[7];
    
    vector<double> dX {
    	y-a*pow(x,3)+b*pow(x,2)-z+I,
    	c-d*pow(x,2)-y,
        r*(s*(x-xR)-z)
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
    double t0 = 0;
    int N = getN();
    double tf = getTf();
    double tol = getTol();
    // Initialize relevant vectors
    vector<double> X0 {
        1.0,
        1.0,
        1.0
    };
    // Initialize params
    vector<double> params {
        1.0,
        3.0,
        1.0,
        5.0,
        1e-3,
        4.0,
        -9.0/5.0,
        10.0
    };
    vector<string> headings {
        "t",
        "x",
        "y",
        "z"
    };
 
    // Write tolerance to file
    writeTol(tol);
 
    // Solve the problem using four different methods and plot the result    
    solveProblem(ODE, X0, t0, tf, tol, N, prec, params, "Hindmarsh-Rose", headings, "3DPlots.py");
}
