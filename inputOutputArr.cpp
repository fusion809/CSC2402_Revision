#include <cassert>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    string input[10];
    int i = 0;

    do {
        getline(cin, input[i]);
        i++;
    } while ((cin) && i < 10);

    for (int j = 0; j < 10; j++) {
        cout << input[j] << endl;
    }
    return 0;
}