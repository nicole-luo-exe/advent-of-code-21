#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string filename = "input.txt";
    ifstream input;

    input.open(filename);

    if (!input.is_open()) {
        cout << "Failed to open file";
        return 1;
    }

    int xVal = 0;
    int yVal = 0;
    int aim = 0;

    while (input) {
        string dir;
        getline(input, dir, ' ');

        int numOfSteps;
        input >> numOfSteps;

        if (dir == "forward") {
            xVal += numOfSteps;
            yVal += aim * numOfSteps;
        } else if (dir == "up") {
            aim -= numOfSteps;
        } else if (dir == "down") {
            aim += numOfSteps;
        }

        input >> ws;
        if (!input) {
            break;
        }
        cout << "'" << dir << "'" << numOfSteps << '\n';
        
    }
    cout << xVal * yVal;
    cout << '\n';
}