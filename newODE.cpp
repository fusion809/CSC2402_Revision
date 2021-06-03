#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

int main() {
    // Filename
    cout << "Input file name:" << endl;
    string filename;
    getline(cin, filename);
    ofstream file;
    file.open(filename);

    // Header
    file << "// Created using newODE.cpp" << endl;
    file << "#include <ODE.h>" << endl;
    file << endl;

    // ODE function
    // Docstring
    file << "/**" << endl;
    file << " * Returns the right-hand side of our ODE (currently the ";
    cout << "Enter the name of the system" << endl;
    string systemName;
    getline(cin, systemName);
    file << systemName << " system)" << endl;
    file << " *" << endl;
    file << " * @param t        A double pertaining to the value of time in our system." << endl;
    file << " * @param X        An array of values of the dependent variables for our ODE." << endl;
    file << " * @param params   An array of parameter values (as doubles) for our ODE." << endl;
    file << " * @return         Vector of dX/dt values." << endl;
    file << " */" << endl;
    file << "vector<double> ODE(double t, vector<double> X, vector<double> params) {" << endl;

    // Body of ODE function
    cout << "Please enter the ODE system you want to solve. Remember " << endl;
    cout << "X is a vector that stores dependent variables. params is a " << endl;
    cout << "vector storing parameters. t is the independent variable." << endl;
    string str;
    getline(cin, str);
    while (cin) {
        getline(cin, str);
        if (str == "done") {
            break;
        }
        file << "    " << str << endl;
    }
    file << "}" << endl;
    file << endl;

    // Main function docstring
    file << "/**" << endl;
    file << " * Main function, takes N (number of steps), tol and tf as user inputs and" << endl; 
    file << " * applies Euler's, Modified Euler's and the Runge-Kutta fourth order method to" << endl;
    file << " * solving the ODE: dX/dt = ODE(t, f, params)" << endl;
    file << " * with the initial condition X(t[0]) = X0, then writes the solution to a CSV" << endl;
    file << " * file and uses a Python script to plot the results." << endl;
    file << " */" << endl;

    // Main function
    file << "int main() {" << endl;
    file << "    // Initialize variables" << endl;
    cout << "Please input the level of precision you want the solution to be written to text files at" << endl;
    file << "    int prec = 15;" << endl;
    double t0;
    cout << "Please enter the starting time (t0)" << endl;
    cin >> t0;
    file << "    double t0 = " << t0 << ";" << endl;
    file << "    int N = getN();" << endl;
    file << "    double tf = getTf();" << endl;
    file << "    double tol = getTol();" << endl;
    file << "    // Initialize relevant vectors" << endl;
    file << "    vector<double> X0 {";
    str = "";
    cout << "Enter initial conditions" << endl;
    while (cin) {
        getline(cin, str);
        if (str == "done") {
            break;
        }
        file << "        " << str << endl;
    }
    file << "    };" << endl;
    file << "    // Initialize params" << endl;
    file << "    vector<double> params {" << endl;
    str = "";
    cout << "Enter parameter values" << endl;
    while (cin) {
        getline(cin, str);
        if (str == "done") {
            break;
        }
        file << "        " << str << endl;
    };
    file << "    };" << endl;
    file << "    vector<string> headings {" << endl;
    str = "";
    cout << "Enter headings" << endl;
    while (cin) {
        getline(cin, str);
        if (str == "done") {
            break;
        }
        file << "        " << str << endl;
    }; 
    file << "    };" << endl;
    file << " " << endl;
    file << "    // Write tolerance to file" << endl;
    file << "    writeTol(tol);" << endl;
    file << " " << endl;
    file << "    // Solve the problem using four different methods and plot the result" << endl;
    cout << "What script do you plan on calling to plot the results?" << endl;
    string scriptName;
    getline(cin, scriptName);
    file << "    solveProblem(ODE, X0, t0, tf, tol, N, prec, params, \"" << systemName << "\", headings, \"" << scriptName << "\");" << endl;
    file << "}" << endl;
    
    file.close();
}