// Required for using vectors
#include <vector>
// Required for assert() calls later
#include <cassert>
// Required for cout and cin calls later
#include <iostream>
#include <iomanip>
// Used later in calls to abs
#include <cmath>
// Required std::generate call later
#include <bits/stdc++.h>

using namespace std;

/**
 * Generates a vector of N+1 linearly spaced points between and including
 * t0 and tf. 
 * 
 * @param t0       Initial t value.
 * @param tf       Final t value.
 * @param N        N+1 t values are stored in the return vector.
 * @return         t vector.
 */
vector<double> linspace(double t0, double tf, int N) {
    double dt = (tf-t0)/N;
    vector<double> t(N+1);
    std::generate(t.begin(), t.end(), [&t0, n = 0, &dt]() mutable { 
        return t0 + n++ * dt; });

    return t;
}

/**
 * Print each entry of vec with "name[index] is:" before it
 * 
 * @param vec      Vector whose elements are of type double.
 * @param name     Name of vector whose elements are to be printed.
 * @return         Nothing.
 */
void printVec(vector<double> vec, string name) {
    for (int i = 0 ; i < vec.size(); i++) {
        cout << name << "[" << i << "] is: " << vec[i] << endl;
    }
}

/**
 * Multiples specified vector by the specified scalar.
 * 
 * @param scalar   Scalar of type double.
 * @param X        Vector of type double.
 * @return         scalar * X.
 */
vector<double> scalMult(double scalar, vector<double> X) {
    // Initialize variables
    int N = X.size();
    vector<double> returnArr(N);

    // Loop over elements of X multiply them by a scalar and assign it to 
    // returnArr
    for (int i = 0; i < N; i++) {
        returnArr[i] = scalar*X[i];
    }

    return returnArr;
}

/**
 * Compute absolute value of each entry in input vector.
 * 
 * @param x        Input vector.
 * @return         Absolute value of x.
 */
vector<double> vecAbs(vector<double> x) {
    // Initialize variables
    int N = x.size();
    vector<double> absx(N);

    // Loop over elements of x[i] and take absolute value
    for (int i = 0; i < N; i++) {
        absx[i] = abs(x[i]);
    }

    return absx;
}

/**
 * Adds the two specified 1d vectors.
 * 
 * @param X        An array of type double.
 * @param Y        An array of type double.
 * @return         Result of X + Y.
 */
vector<double> vecAdd(vector<double> X, vector<double> Y) {
    // Initialize variable
    int N = X.size();
    vector<double> returnArr(N);

    // Check if X and Y match in size; if they don't throw an error
    assert(X.size() == Y.size());

    // For loop was originally used but returned a bizarre error
    for (int i = 0 ; i < N; i++) {
        returnArr[i] = X[i]+Y[i];
    }

    return returnArr;
}

/**
 * Multiplies the two specified vectors.
 * 
 * @param X        An array of type double.
 * @param Y        An array of type double.
 * @return         X * Y element-wise.
 */
vector<double> vecMult(vector<double> X, vector<double> Y) {
    // Initialize variables
    int N = X.size();
    vector<double> returnArr(N);

    // Check if X and Y match in size; if they don't throw an error
    assert(X.size() == Y.size());

    for (int i = 0; i < N; i++) {
        returnArr[i] = X[i]*Y[i];
    }

    return returnArr;
}