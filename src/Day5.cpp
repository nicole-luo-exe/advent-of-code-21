#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define REP(i, start, end) for (i = start; i <= end; ++i)
#define isHorizontal(x) x.first.second == x.second.second
#define isVertical(x) x.first.first == x.second.first

typedef pair<int, int> pii;
typedef pair<pair<int, int>, pair<int, int> > line;

void insertDiagonal(line& l, map<pii, int>& m);
void insert(line& l, map<pii, int>& m, bool isHorLine);
void insertHelper(int x, int y, map<pii, int>& m);

int main() {
    map<pii, int> freqCount;

    int x;
    while (cin >> x) {
        char c;
        line l;
        l.first.first = x;
        cin >> c >> l.first.second >> c >> c >> l.second.first >> c >> l.second.second;
        if (isHorizontal(l)) {
            //cout << "Start: " << l.first.first << ", "<< l.first.second << "\t End: " << l.second.first << ", " << l.second.second << '\n';
            insert(l, freqCount, true);
        } else if (isVertical(l)) {
            insert(l, freqCount, false);
        } else {
            insertDiagonal(l, freqCount);
        }
        
    }
    
    int overlaps = 0;
    for (auto itr = freqCount.begin(); itr != freqCount.end(); ++itr) {
        if (itr->second > 1) {
            overlaps++;
        }
    }
    cout << overlaps << '\n';
}

void insertDiagonal(line& l, map<pii, int>& m) {
    int minx = min(l.first.first, l.second.first);
    int maxx = max(l.first.first, l.second.first);
    int miny = min(l.first.second, l.second.second);
    int maxy = max(l.first.second, l.second.second);
    int x, y;
    if (l.first.first == minx) {
        if (l.first.second == miny) {
            x = minx;
            y = miny;
            while (x <= maxx) {
                insertHelper(x, y, m);
                x++;
                y++;
            }
        } else {
            x = minx;
            y = maxy; 
            while (x <= maxx) {
                insertHelper(x, y, m);
                x++;
                y--;
            }
        }
    } else {
        if (l.first.second == miny) {
            x = maxx;
            y = miny;
            while (x >= minx) {
                insertHelper(x, y, m);
                x--;
                y++;
            }
        } else {
            x = maxx;
            y = maxy;
            while (x >= minx) {
                insertHelper(x, y, m);
                x--;
                y--;
            }
        }
    }
}

void insertHelper(int x, int y, map<pii, int>& m) {
    pii coord (x, y);
    if (m.find(coord) != m.end()) {
        m[coord]++;
    } else {
        m[coord] = 1;
    }
}

void insert(line& l, map<pii, int>& m, bool isHorLine) {
    int start, end;
    if (isHorLine) {
        int y = l.first.second;
        start = min(l.first.first, l.second.first);
        end = max(l.first.first, l.second.first);
        for (int i = start; i <= end; ++i) {
            insertHelper(i, y, m);
        }
    } else {
        int x = l.first.first;
        start = min(l.first.second, l.second.second);
        end = max(l.first.second, l.second.second);
        for (int i = start; i <= end; ++i) {
            insertHelper(x, i, m);
        }
    }
}

//error is bc the start might be greater than end -> those lines not acocunted for