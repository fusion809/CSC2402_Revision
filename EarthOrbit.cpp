// Created using newODE.cpp
#include <ODE.h>

/**
 * Returns the right-hand side of our ODE (currently the orbit of the Earth)
 *
 * @param t        A double pertaining to the value of time in our system.
 * @param X        An array of values of the dependent variables for our ODE.
 * @param params   An array of parameter values (as doubles) for our ODE.
 * @return         Vector of dX/dt values.
 */
vector<double> ODE(double t, vector<double> X, vector<double> params) {
    // Extract dependent variables from X vector
    double r = X[0];
    double dr = X[1];
    double theta = X[2];
    
    // Constants
    double G = 6.674e-11; // Gravitational constant
    double M = params[0]; // Mass of the Earth (kg)
    double c = params[1]; // This is equal to r^2 theta = angular momentum/moon mass
    
    // Initialize derivative vector
    // These equations were obtained from the Euler-Lagrange equations from
    // the Lagrangian:
    // m/2 * (rdot^2 + r^2 theta dot^2) + GMm/r.
    vector<double> dX {
    	dr,                               // dr/dt
    	pow(c,2)/pow(r,3)-G*M/pow(r,2),   // d^2r/dt^2
        c/pow(r,2)                        // dtheta/dt
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
    int N = int (1e4);
    double tf = 6.32e7;
    double tol = 1e-8;
    // int N = getN();
    // double tf = getTf();
    // double tol = getTol();
    // Initialize relevant vectors
    vector<double> X0 {
        149.6e9,
        350,
        0
    };
    // Initialize params
    vector<double> params {
        1.9885e30,
        4.4405e15
    };
    vector<string> headings {
        "t",
        "r",
        "dr",
        "theta"
    };
 
    // Write tolerance to file
    writeTol(tol);
 
    // Solve the problem using four different methods and plot the result    
    solveProblem(ODE, X0, t0, tf, tol, N, prec, params, "EarthOrbit", headings, "2DPlotsEarthOrbit.py");
}
