// Used to write to file
#include <fstream>
// Required for system call later
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

// Load required namespace
using namespace std;

#include <vecOps.h>
#include <input.h>

/**
 * Solution object class.
 */
class solClass {
    public:
        // Simplest constructor
        solClass(vector<double>, vector<vector<double>>);
        // RKF45 constructor
        solClass(vector<double>(*f)(double, vector<double>, vector<double>), 
        vector<double>, double, double, vector<double>, double, int, double);
        // Constructor that uses other methods
        solClass(vector<double>(*f)(double, vector<double>, vector<double>), 
        vector<double>, vector<double>, vector<double>, string);

        // Write to CSV
        void writeToCSV(int, string, vector<string>);
 
    private:
        // Solution variables.
        // No compelling reason they need to be private, but they can be.
        vector<double> t;
        vector<vector<double>> X;
};

/**
 * Write solution to CSV file.
 * 
 * @param prec     Precision to which the solution should be written to the 
 * CSV file.
 * @param filename Filename (including file extension) of file that solution 
 * is to be written to.
 * @param headings Vector containing headings for each variable to be written 
 * to the file.
 */
void solClass::writeToCSV(int prec, string filename, vector<string> headings) {
    if (headings.size() != X[0].size() + 1) {
        cout << "There should be a heading for t and each variable in the";
        cout << " separate columns of X" << endl;
        throw;
    }
    int N = t.size();

    // Open file
    ofstream file;
    file.open(filename);

    // Write headings to file
    for (int i = 0 ; i < headings.size(); i++) {
        if (i != headings.size()-1) {
            file << headings[i] << ",";
        } else {
            file << headings[i] << endl;
        }
    }

    // Write solution to file
    for (int i = 0; i < N; i++) {
        file << t[i] << setprecision(prec) << ",";
        for (int j = 1 ; j < headings.size()-1; j++) {
            file << X[i][j-1] << ",";
        }
        file << X[i][headings.size()-2] << endl;
    }
}

/**
 * Constructor for solClass.
 * 
 * @param tInput   t vector that the t member variable is to be set to.
 * @param XInput   X vector that the X member variable is to be set to.
 */
solClass::solClass(vector<double> tInput, vector<vector<double>> XInput) {
    t = tInput;
    X = XInput;
}

/**
 * Applies Euler's method to solving the ODE:
 * dX/dt = f(t, X, params)
 * where X(t[0]) = X0.
 * 
 * @param f        Function that takes the arguments time value (scalar),
 * corresponding X array and params and returns dX/dt. 
 * @param X0       X at t[0].
 * @param t        Vector of type double consisting of time values we want 
 * the solution at.
 * @param params   Vector of type double consisting of parameter values.
 * @return         2d array of X values; rows correspond to different t values.
 */
vector<vector<double>> Euler(vector<double>(*f)(double, vector<double>, 
vector<double>), vector<double> X0, vector<double> t, vector<double> params) {
    // Initializing variables
    double dt;
    int N = t.size()-1;
    vector<vector<double>> X;
    vector<double> nextX;

    // First entry should be X0
    X.push_back(X0);

    // Loop over time values
    for (int i = 0; i < N; i++) {
        dt = t[i+1]-t[i];
        nextX = vecAdd(X[i], scalMult(dt, f(t[i], X[i], params)));
        X.push_back(nextX);
    }

    return X;
}

/**
 * Applies Modified Euler's method to solving the ODE:
 * dX/dt = f(t, X, params)
 * where X(t[0]) = X0.
 * 
 * @param f        Function that takes the arguments time value (scalar),
 * corresponding X array and params and returns dX/dt. 
 * @param X0       X at t[0].
 * @param t        Vector of type double consisting of time values we want 
 * the solution at.
 * @param params   Vector of type double consisting of parameter values.
 * @return         2d array of X values; rows correspond to different t values.
 */
vector<vector<double>> ModEuler(vector<double>(*f)(double, vector<double>, 
vector<double>), vector<double> X0, vector<double> t, vector<double> params) {
    // Initializing variables
    double dt;
    int N = t.size()-1;
    int sysSize = X0.size();
    vector<vector<double>> X;
    vector<double> nextX(sysSize), k1(sysSize), k2(sysSize);

    // First entry should be X0
    X.push_back(X0);

    // Loop over time values
    for (int i = 0; i < N; i++) {
        dt = t[i+1]-t[i];
        k1 = scalMult(dt, f(t[i], X[i], params));
        k2 = scalMult(dt, f(t[i+1], vecAdd(X[i], k1), params));
        nextX = vecAdd(X[i], scalMult(0.5, vecAdd(k1, k2)));
        X.push_back(nextX);
    }

    return X;
}

/**
 * Applies Runge-Kutta fourth-order method to solving the ODE:
 * dX/dt = f(t, X, params)
 * where X(t[0]) = X0.
 * 
 * @param f        Function that takes the arguments time value (scalar),
 * corresponding X array and params and returns dX/dt. 
 * @param X0       X at t[0].
 * @param t        Vector of type double consisting of time values we want 
 * the solution at.
 * @param params   Vector of type double consisting of parameter values.
 * @return         2d array of X values; rows correspond to different t values.
 */
vector<vector<double>> RK4(vector<double>(*f)(double, vector<double>, 
vector<double>), vector<double> X0, vector<double> t, vector<double> params) {
    // Initializing variables
    double dt;
    int N = t.size()-1;
    int sysSize = X0.size();
    vector<vector<double>> X;
    vector<double> nextX(sysSize), k1(sysSize), k2(sysSize), k3(sysSize);
    vector<double> k4(sysSize);

    // First entry should be X0
    X.push_back(X0);

    // Loop over time values
    for (int i = 0; i < N; i++) {
        dt = t[i+1]-t[i];
        k1 = scalMult(dt, f(t[i], X[i], params));
        k2 = scalMult(dt, f(t[i]+dt/2, vecAdd(X[i], scalMult(0.5, k1)), params));
        k3 = scalMult(dt, f(t[i]+dt/2, vecAdd(X[i], scalMult(0.5, k2)), params));
        k4 = scalMult(dt, f(t[i]+dt, vecAdd(X[i], k3), params));
        nextX = vecAdd(X[i], scalMult(1.0/6.0, vecAdd(vecAdd(vecAdd(k1, 
        scalMult(2, k2)), scalMult(2, k3)), k4)));
        X.push_back(nextX);
    }

    return X;
}

/**
 * Applies the Runge-Kutta-Fehlberg 4/5th order method to solving the ODE:
 * dX/dt = f(t, X, params)
 * where X(t0) = X0. 
 * 
 * @param f        Function that takes the arguments time value (scalar),
 * corresponding X array and params and returns dX/dt. 
 * @param X0       X at t0.
 * @param t0       Starting t value.
 * @param tf       Final t value.
 * @param params   Vector of type double consisting of parameter values.
 * @param tol      A double representing the error tolerance to be used 
 * (default=1e-9).
 * @param itMax    An integer representing the maximum number of iterations 
 * allowable.
 * @param dtInit   Initial guess for dt. 
 * @return         Object of type solClass containing computed t and X values.
 */
solClass RKF45(vector<double>(*f)(double, vector<double>, vector<double>), 
vector<double> X0, double t0, double tf, vector<double> params, 
double tol=1e-9, int itMax=1000000, double dtInit=1e-1) {
    // Initialize required vectors
    vector<double> t;
    vector<vector<double>> X;
    vector<double> k1, k2X, k2, k3X, k3, k4X, k4, k5X, k5, k6X, k6, X1, X2, RX;

    // Add first entries to t and X
    t.push_back(t0);
    X.push_back(X0);

    // Initialize scalar variables
    double R;
    int i = 0;
    double s;
    double dt = dtInit;

    // Loop over time until either t[i] = tf is reached or we exceed the 
    // maximum number of iterations.
    while ( ( t[i] < tf ) && (i < itMax)) {
        dt = std::min(dt, tf-t[i]);

        // Predictor-correctors
        k1 = scalMult(dt, f(t[i], X[i], params));
        k2X = vecAdd(X[i], scalMult(1.0/4.0, k1));
        k2 = scalMult(dt, f(t[i] + dt/4.0, k2X, params));
        k3X = vecAdd(vecAdd(X[i], scalMult(3.0/32.0, k1)), 
        scalMult(9.0/32.0, k2));
        k3 = scalMult(dt, f(t[i] + 3.0*dt/8.0, k3X, params));
        k4X = vecAdd(vecAdd(vecAdd(X[i], scalMult(1932.0/2197.0, k1)), 
        scalMult(-7200.0/2197.0, k2)), scalMult(7296.0/2197.0, k3));
        k4 = scalMult(dt, f(t[i] + 12.0*dt/13.0, k4X, params));
        k5X = vecAdd(vecAdd(vecAdd(vecAdd(X[i], scalMult(439.0/216.0, k1)), 
        scalMult(-8.0, k2)), scalMult(3680.0/513.0, k3)), 
        scalMult(-845.0/4104.0, k4));
        k5 = scalMult(dt, f(t[i]+dt, k5X, params));
        k6X = vecAdd(vecAdd(vecAdd(vecAdd(vecAdd(X[i], 
        scalMult(-8.0/27.0, k1)), scalMult(2.0, k2)), 
        scalMult(-3544.0/2565.0, k3)), scalMult(1859.0/4104.0, k4)), 
        scalMult(-11.0/40.0, k5));
        k6 = scalMult(dt, f(t[i]+dt/2.0, k6X, params));

        // 4th and 5th order approximation to X[i+1]
        X1 = vecAdd(vecAdd(vecAdd(vecAdd(X[i], scalMult(25.0/216.0, k1)), 
        scalMult(1408.0/2565.0, k3)), scalMult(2197.0/4104.0, k4)), 
        scalMult(-1.0/5.0, k5));
        X2 = vecAdd(vecAdd(vecAdd(vecAdd(vecAdd(X[i], 
        scalMult(16.0/135.0, k1)), scalMult(6656.0/12825.0, k3)), 
        scalMult(28561.0/56430.0, k4)), scalMult(-9.0/50.0, k5)), 
        scalMult(2.0/55.0, k6));

        // Measure of error in X1
        RX = scalMult(pow(dt, -1), vecAbs(vecAdd(X1, scalMult(-1.0, X2))));
        R = *max_element(RX.begin(), RX.end());

        // Adjust step size scaling factor according to R
        if (R != 0) {
            s = pow(tol/(2.0*R), 0.25);
        } else {
            s = 1.0;
        }

        // If R is below error tolerance move on to next step
        if (R <= tol) {
            t.push_back(t[i]+dt);
            X.push_back(X1);
            i++;
        }

        // Adjust step size by scaling factor
        dt *= s;
    }

    // Write to solution object
    solClass solution(t, X);

    return solution;
}

/**
 * Constructor for solClass that uses specified method to solve ODE for 
 * specified t values with specified initial condition and writes t and X to
 * solClass object.
 * 
 * @param f        Function that takes the arguments time value (scalar),
 * corresponding X array and params and returns dX/dt. 
 * @param X0       X at tInput[0].
 * @param tInput   Vector of type double consisting of time values we want 
 * the solution at.
 * @param params   Vector of type double consisting of parameter values.
 * @param method   Non-adaptive method to be used to integrate ODE. Accepted
 * @return         N/A.
 */
solClass::solClass(vector<double>(*f)(double, vector<double>, vector<double>), 
vector<double> X0, vector<double> tInput, vector<double> params, 
string method="RK4") {
    t = tInput;
    if (method == "RK4") {
        X = RK4(f, X0, tInput, params);
    } else if (method == "Euler") {
        X = Euler(f, X0, tInput, params);
    } else if (method == "ModEuler") {
        X = ModEuler(f, X0, tInput, params);
    } else {
        cout << "No method called " << method << " is callable by this";
        cout << " constructor." << endl;
    }
}

/**
 * Constructor for solClass that uses RKF45 to initialize t and X.
 * 
 * @param f        Function that takes the arguments time value (scalar),
 * corresponding X array and params and returns dX/dt. 
 * @param X0       X at t0.
 * @param t0       Starting t value.
 * @param tf       Final t value.
 * @param params   Vector of type double consisting of parameter values.
 * @param tol      A double representing the error tolerance to be used 
 * (default=1e-9).
 * @param itMax    An integer representing the maximum number of iterations 
 * allowable.
 * @param dtInit   Initial guess for dt. 
 * @return         N/A.
 */
solClass::solClass(vector<double>(*f)(double, vector<double>, vector<double>), 
vector<double> X0, double t0, double tf, vector<double> params, 
double tol=1e-9, int itMax=1000000, double dtInit=1e-1) {
    *this = RKF45(f, X0, t0, tf, params, tol, itMax, dtInit);
}

/**
 * Solve the ODE using the four algorithms implemented in ODE.h and produce
 * plots in SVG using Python's Matplotlib.
 * 
 * @param f        Function that returns dX/dt from the arguments t, X and 
 * params.
 * @param X0       Initial condition.
 * @param t0       Initial time.
 * @param tf       Final time.
 * @param tol      Error tolerance.
 * @param N        Number of steps to be used; t array for Euler, ModEuler 
 * and RK4 will have N+1 elements.
 * @param prec     The precision solution is to be written to CSV files at.
 * @param params   A vector of parameters for f.
 * @param prob     String containing problem name.
 * @param headings Vector of headings to be used in CSV file.
 * @param pyScript Python script file name (including file extension).
 * @return         Nothing.
 */
void solveProblem(vector<double> (*f)(double, vector<double>, vector<double>), 
vector<double> X0, double t0, double tf, double tol, int N, int prec, 
vector<double> params, string prob, vector<string> headings, string pyScript) {
    // This makes t equivalent to np.linspace(t0, tf, num=N+1)
    vector<double> t = linspace(t0, tf, N);

    // Initialize solution objects
    solClass EulerSol(f, X0, t, params, "Euler");
    solClass ModEulerSol(f, X0, t, params, "ModEuler");
    solClass RK4Sol(f, X0, t, params, "RK4");
    solClass solution(f, X0, t0, tf, params, tol);

    // Write solution data to CSV file (easiest to import into Python)
    EulerSol.writeToCSV(prec, "Example3_Euler.csv", headings);
    ModEulerSol.writeToCSV(prec, "Example3_ModEuler.csv", headings);
    RK4Sol.writeToCSV(prec, "Example3_RK4.csv", headings);
    solution.writeToCSV(prec, "Example3_RKF45.csv", headings);
    
    // Write prob to file so Python script can use it
    ofstream file;
    file.open("Example3_prob.txt");
    file << prob;
    file.close();

    // Use Python to generate relevant plots and save as svgs
    stringstream cmd;
    cmd << "python ";
    cmd << pyScript;
    system(cmd.str().c_str());
}