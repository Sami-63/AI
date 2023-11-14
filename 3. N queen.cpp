#include<bits/stdc++.h>
using namespace std;
const int N = 8;
int step=0;
// OLI's code
void printBoard(const vector<int>& board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j)
                cout << "Q ";
            else
                cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

int cal_conflicts(const vector<int>& board) {
    int conflicts = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (board[i] == board[j] || abs(i - j) == abs(board[i] - board[j]))
                conflicts++;
        }
    }
    return conflicts;
}

void solveQueens() {
    srand(time(nullptr));

    vector<int> board(N);
    vector<int> temp(N);
    for (int i = 0; i < N; i++) {
        board[i] = rand() % N;
    }

    int cur_conflict = cal_conflicts(board);

    cout << "inital state:=" << endl<< " " << " heuristic value is : " << cur_conflict << "):" << endl;
    printBoard(board);

    while (cur_conflict > 0) {
        int minConflicts = cur_conflict;
        vector<vector<int>> nextStates;

        for (int i = 0; i < N; i++) {
            temp = board;
            for (int j = 0; j < N; j++) {
                temp[i] = j;
                int tempConflicts = cal_conflicts(temp);
                if (tempConflicts < minConflicts) {
                    minConflicts = tempConflicts;
                    nextStates.clear();
                    nextStates.push_back(temp);
                } else if (tempConflicts == minConflicts) {
                    nextStates.push_back(temp);
                }
            }
        }

        if (minConflicts == cur_conflict) {
            for (int i = 0; i < N; i++) {
                board[i] = rand() % N;
            }
            cur_conflict = cal_conflicts(board);

        } else {
            int randomIndex = rand() % nextStates.size();

            board = nextStates[randomIndex];
            cur_conflict = minConflicts;
        }

        cout << "step number:=" << ++step << " " << " heuristic value is : " << cur_conflict << "):" << endl;
        printBoard(board);
    }

    cout << "Solution found:" << endl;
    printBoard(board);
}

int main() {
    solveQueens();
    return 0;
}