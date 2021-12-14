#include <iostream>
#include <vector>
using namespace std;


int main() {
    vector<long> fishes (9, 0);
    int timer;
    while (cin >> timer) {
        fishes[timer]++;
        char comma;
        cin >> comma;
    }
    int days = 0;
    while (days < 80) {
        vector<long> next (9, 0);
        for (int i = 0; i < 9; i++) {
            if (i == 0) {
                next[8] = fishes[0];
                next[6] += fishes[0];
            } else {
                next[i - 1] += fishes[i];
            }
        }
        fishes = next;
        days++;
    }

    long sum = 0;
    for (long i : fishes) {
        sum += i;
    }
    cout << sum << '\n';
}