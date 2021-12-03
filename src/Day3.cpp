#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <list>
#include <iterator>
using namespace std;

long getRating(list<int> indexes, string inputs[], bool isOxy);
list<int> narrowDown(list<int> indexToFocusOn, int charIndex, string inputs[], bool isOxy);

int main() {
    string filename = "input.txt";
    ifstream input;

    input.open(filename);

    int lineCount = 0;
    int zeroCount = 0;

    list <string> lines;

    list <int> oxyRatingIndexes, carboRatingIndexes;
    list <int> zeroIndexes, oneIndexes;

    while (input) {
        string line;
        getline(input, line);

        if (line[0] == '0') {
            zeroCount++;
            zeroIndexes.push_back(lineCount);
        } else {
            oneIndexes.push_back(lineCount);
        }

        lines.push_back(line);

        lineCount++;
        
        input >> ws;
        if (!input) {
            break;
        }
    }

    if (zeroCount * 2 > lineCount) {
        oxyRatingIndexes = zeroIndexes;
        carboRatingIndexes = oneIndexes;
    } else {
        oxyRatingIndexes = oneIndexes;
        carboRatingIndexes = zeroIndexes;
    }

    cout << "oxy lines = " << oxyRatingIndexes.size() << '\n';
    cout << "carb lines = " << carboRatingIndexes.size() << '\n';

    string inputs[lines.size()];
    std::copy(lines.begin(), lines.end(), inputs);

    cout << getRating(oxyRatingIndexes, inputs, true) * getRating(carboRatingIndexes, inputs, false);
}

long getRating(list<int> indexes, string inputs[], bool isOxy) {
    int i = 1;
    list<int> temp = indexes;
    while (temp.size() != 1) {
        list<int> next = narrowDown(temp, i, inputs, isOxy);
        temp = next;
        i++;
    }

    return stol(inputs[temp.front()], nullptr, 2);
}

list<int> narrowDown(list<int> indexToFocusOn, int charIndex, string inputs[], bool isOxy) {
    list <int> :: iterator it;
    list <int> zeroIndexes, oneIndexes;
    int zeroCount = 0;
    if (indexToFocusOn.size() == 1) return indexToFocusOn;

    for (it = indexToFocusOn.begin(); it != indexToFocusOn.end(); it++) {
        if (inputs[*it][charIndex] == '0') {
            zeroCount++;
            zeroIndexes.push_back(*it);
        } else {
            oneIndexes.push_back(*it);
        }
    }
    if (isOxy) {
        return zeroCount * 2 > indexToFocusOn.size() ? zeroIndexes : oneIndexes;
    } else {
        return zeroCount * 2 <= indexToFocusOn.size() ? zeroIndexes : oneIndexes;
    }
}

//part one
/*
int main() {
    string filename = "input.txt";
    ifstream input;

    input.open(filename);

    string line;
    getline(input, line);

    int lineCount = 1;
    int length = line.length();
    int zeroCount[length];

    for (int i = 0; i < length; i++) {
        zeroCount[i] = 0;
    }

    countZeros(line, zeroCount, length);

    while (input) {
        getline(input, line);

        countZeros(line, zeroCount, length);

        lineCount++;

        input >> ws;
        if (!input) {
            break;
        }
    }

    int benchmark = lineCount / 2;
    int gammaRate = 0;
    int epsRate = 0;

    for (int i = 0; i < length; i++) {
        gammaRate = gammaRate<<1;
        epsRate = epsRate<<1;
        if (zeroCount[i] > benchmark) {
            epsRate += 1;
        } else {
            gammaRate += 1;
        }
    }

    cout << gammaRate * epsRate << '\n';
}

void countZeros(string s , int count[], int size) {
    for (int i = 0; i < size; i++) {
        if (s[i] == '0') {
            count[i]++; 
        }
    }
}
*/