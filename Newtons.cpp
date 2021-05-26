#include <cassert>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

/**
 * Object containing function values and Jacobian components.
 */ 
class newtonRetnCont {
    public:
        vector<double> F;
        vector<double> Jacobian;
};

/**
 * Return object of type newtonRetnCont containing function and Jacobian values
 * corresponding to the inputs. 
 * 
 * @param X        Vector of x and y values.
 * @param params   Vector of parameter values.
 * @return         An object containing vectors of function and Jacobian 
 * values.
 */
newtonRetnCont fgJacob(vector<double> X, vector<double>params) {
    // Set variables according to parameters
    double p = params[0];
    double x = X[0];
    double y = X[1];

    // Initialize vectors we'll store in object
    vector<double> fn;
    vector<double> Jacobian;

    // Fill vectors with required values
    fn.push_back(pow(x, 2) + 9*pow(y,2)-16);
    fn.push_back(y - pow(x,2) + 2*x -p);
    Jacobian.push_back(2*x);
    Jacobian.push_back(18*y);
    Jacobian.push_back(-2*x+2);
    Jacobian.push_back(1);

    // Store fn and Jacobian in object
    newtonRetnCont object;
    object.F = fn;
    object.Jacobian = Jacobian;

    return object;
}

/**
 * Compute absolute value of each entry in input vector.
 * 
 * @param x        Input vector.
 * @return         Absolute value of x.
 */
vector<double> vecAbs(vector<double> x) {
    vector <double> absx;
    for (int i = 0; i < x.size(); i++) {
        absx.push_back(abs(x[i]));
    }

    return absx;
}

/**
 * Solves specified system f(X, params) = 0
 */
vector<double> newtons(newtonRetnCont(*f)(vector<double>, vector<double>), vector<double> X0, vector<double> params, double tol=1e-10, int itMax=1000) {
    // Initialize variables
    vector<vector<double>> X;
    vector<double> nextX;
    int i = 0;
    double detm;

    // Initialize fn, Jacobian, absfn and r
    newtonRetnCont newtonRetnObj = f(X0, params);
    vector<double> fn = newtonRetnObj.F;
    vector<double> Jacobian = newtonRetnObj.Jacobian;
    vector<double> absfn = vecAbs(fn);
    double r = *max_element(absfn.begin(), absfn.end());

    // Start X with X0.
    X.push_back(X0);

    // Iterate until r goes below tol or i exceeds itMax
    while ( ( r >= tol) && (i < itMax) ) {
        newtonRetnObj = f(X[i], params);
        fn = newtonRetnObj.F;
        Jacobian = newtonRetnObj.Jacobian;
        absfn = vecAbs(fn);
        r = *max_element(absfn.begin(), absfn.end());
        detm = Jacobian[0] * Jacobian[3] - Jacobian[1] * Jacobian[2];
        if (i == 0) {
            nextX.push_back(X[i][0] - (fn[0]*Jacobian[3] - fn[1]*Jacobian[1])/detm);
            nextX.push_back(X[i][1] - (fn[1]*Jacobian[0] - fn[0]*Jacobian[2])/detm);
        } else {
            nextX[0] = X[i][0] - (fn[0]*Jacobian[3] - fn[1]*Jacobian[1])/detm;
            nextX[1] = X[i][1] - (fn[1]*Jacobian[0] - fn[0]*Jacobian[2])/detm;
        }
        X.push_back(nextX);
        i++;
    }

    if (i == itMax) {
        cout << "Maximum number of iterations exceeded!" << endl;
    }

    return X[i];
}

void print(vector<double> X, int N) {
    for (int i = 0; i < X.size(); i++) {
        if (i == X.size()-1) {
            cout << "X[" << i << "] is: " << setprecision(N) << X[i] << endl;
        } else {
            cout << "X[" << i << "] is: " << setprecision(N) << X[i] << ", ";
        }
    }
}

int main() {
    vector<double> X0;
    vector<vector<double>> X;
    vector<double> params;
    vector<double> p;

    // Initialize X0
    X0.push_back(0);
    X0.push_back(1.3);

    // Initialize params vec
    int N = 2000;
    double p0 = 0;
    double pf = 2.0;
    p.push_back(p0);
    params.push_back(p0);

    // Solve for X0
    X.push_back(newtons(fgJacob, X0, params));
    print(X[0], 15);

    for (int i = 1 ; i <= N ; i++) {
        p.push_back(p0 + i * (pf-p0)/N);
        params[0] = p[i];
        X.push_back(newtons(fgJacob, X[i-1], params));
        cout << "i is: " << i << ", ";
        cout << "p[i] is: " << p[i] << ", ";
        print(X[i], 15);
    }
}