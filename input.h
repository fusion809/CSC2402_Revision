#include <iostream>

using namespace std;

/**
 * Get the number of steps to be used (N) from the user.
 * 
 * @params         None.
 * @return         N.
 */
int getN() {
    double doubleN;
    cout << "Please enter N:" << endl;
    // Following two lines allows users to enter N in scientific notation
    cin >> doubleN;
    int N = int (doubleN);

    return N;
}

/**
 * Get the final t value (tf) from the user.
 * 
 * @params         None.
 * @return         tf.
 */
double getTf() {
    double tf;
    cout << "Please enter tf:" << endl;
    cin >> tf;
    
    return tf;
}

/**
 * Get the error tolerance (tol) from the user.
 * 
 * @params         None.
 * @return         tol.
 */
double getTol() {
    double tol;
    cout << "Please enter tol for RKF45:" << endl;
    cin >> tol;

    return tol;
}