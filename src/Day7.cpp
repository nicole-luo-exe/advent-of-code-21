#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

long getTotalFuel(int chosenPos, vector<int>& positions);
int getFuelCost(int chosenPos, int pos);

int main() {
    vector<int> positions;
    int p;
    char c;
    while (cin >> p) {
        positions.push_back(p);
        cin >> c;
    }
    std::sort(positions.begin(), positions.end());
    int n = positions.size();
    
    cout << "num elements: " << positions.size() << '\n';
    
    int start = positions[0];
    int end = positions[n - 1];
    while (start < end) {
        int med = (start + end) / 2;
        if (getTotalFuel(med - 1, positions) > getTotalFuel(med, positions)) {
            start = med;
        } else {
            end = med - 1;
        }
        //cout << "start: " << start << "\t end: " << end << '\n';
    }
    // for (int i : positions) {
    //     fuel += abs(positions[499] - i);
    // }

    cout << getTotalFuel(end, positions) << '\n';

}

long getTotalFuel(int chosenPos, vector<int>& positions) {
    long fuel = 0;
    for (int i : positions) {
        fuel += getFuelCost(chosenPos, i);
    }
    return fuel;
}

int getFuelCost(int chosenPos, int pos) {
    int n = abs(chosenPos - pos);
    return 0.5 * n * (n + 1);
}