#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<vector<bool> > createBoard();
vector<int> parseNumbersCalled(string str);
unordered_map<int, pair<int, int> > parseBoards(string board[]);
bool markBoard(vector<vector<bool> >& board, int x, int y);
int calculateSum(unordered_map<int, pair<int, int> >& boardNum);


//commented out part 1 soln

int main() {
    ifstream input;
    input.open("input.txt");

    string numbersCalled;
    getline(input, numbersCalled);
    input >> ws;
    vector<int> nums = parseNumbersCalled(numbersCalled);
    string strboard[5];
    vector<unordered_map<int, pair<int, int> > > boardNums;
    vector<vector<vector<bool> > > boards;

    int winNum = -1;
    int numWon = 0;
    int lastBoardIndex = -1;
    //int winBoardIndex = -1;

    while (input) {
        int i = 0;
        while (i < 5) {
            string line;
            getline(input, line);
            strboard[i] = line;
            i++;
        }
        if (!input) {
            break;
        }
        boardNums.push_back(parseBoards(strboard));
        boards.push_back(createBoard());
        input >> ws;
    }

    int boardCount = boardNums.size();
    vector<bool> hasWon(boardCount, false);

    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < boardCount; j++) {
            if (boardNums[j].find(nums[i]) != boardNums[j].end()) {
                pair<int, int> pos = boardNums[j][nums[i]];
                boardNums[j].erase(nums[i]);
                if (markBoard(boards[j], pos.first, pos.second)) {
                    if (!hasWon[j]) {
                        hasWon[j] = true;
                        numWon++;
                        //cout << numWon << '\n';
                    }
                    if (numWon == boardCount) {
                        winNum = nums[i];
                        lastBoardIndex = j;
                        break;
                    }
                    // winNum = nums[i];
                    // winBoardIndex = j;
                    // break;
                }
            }
        }
        if (winNum != -1) break;
    }

    //cout << calculateSum(boardNums[winBoardIndex]) * winNum << '\n';
    cout << calculateSum(boardNums[lastBoardIndex]) * winNum << '\n';
}

vector<vector<bool> > createBoard() {
    vector<bool> row(5, false);
    return vector<vector<bool> > (5, row);
}

vector<int> parseNumbersCalled(string str) {
    vector<int> v;
 
    stringstream ss(str);
 
    for (int i; ss >> i;) {
        v.push_back(i);    
        if (ss.peek() == ',')
            ss.ignore();
    }

    return v;
}

unordered_map<int, pair<int, int> > parseBoards(string board[]) {
    unordered_map<int, pair<int, int> > boardNum;
    for (int i = 0; i < 5; i++) {
        int k = 0;
        stringstream ss(board[i]);
        for (int j; ss >> j;) {
            pair<int, int> pos;
            pos.first = i;
            pos.second = k;
            boardNum[j] = pos;
            k++;
            if (ss.peek() == ' ')
                ss.ignore();
        }
    }
    return boardNum;
}

bool markBoard(vector<vector<bool> >& board, int x, int y) {
    board[x][y] = true;
    bool isRowComplete = board[0][y] && board[1][y] && board[2][y] && board[3][y] && board[4][y];
    bool isColComplete = board[x][0] && board[x][1] && board[x][2] && board[x][3] && board[x][4];
    return isRowComplete || isColComplete;
}

int calculateSum(unordered_map<int, pair<int, int> >& boardNum) {
    int sum = 0;

    for (auto itr = boardNum.begin(); itr != boardNum.end(); ++itr) {
        sum += itr->first;
    }
    return sum;
}
