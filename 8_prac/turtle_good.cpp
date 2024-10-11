#include <vector>
#include <limits>
#include <iostream>
#include <climits>

using namespace std;

struct Cell {
    int north_time, east_time;
};

struct Point {
    int x, y;
};

enum Direction { NORTH, EAST };

int minTime(vector<vector<Cell>>& grid, Point A, Point B, vector<vector<Direction>>& dir) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<int>> dp(rows, vector<int>(cols, INT_MAX));
    dp[A.x][A.y] = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i > 0) {
                if (dp[i][j] > dp[i-1][j] + grid[i-1][j].north_time) {
                    dp[i][j] = dp[i-1][j] + grid[i-1][j].north_time;
                    dir[i][j] = NORTH;
                }
            }
            if (j > 0) {
                if (dp[i][j] > dp[i][j-1] + grid[i][j-1].east_time) {
                    dp[i][j] = dp[i][j-1] + grid[i][j-1].east_time;
                    dir[i][j] = EAST;
                }
            }
        }
    }

    return dp[B.x][B.y];
}

void printPath(vector<vector<Direction>>& dir, Point B) {
    int i = B.x, j = B.y;
    cout << "Path: ";
    while (i > 0 || j > 0) {
        if (dir[i][j] == NORTH) {
            cout << "N ";
            i--;
        } else {
            cout << "E ";
            j--;
        }
    }
    cout << endl;
}

int main() {
    // Example grid with passage times
    vector<vector<Cell>> grid = {
            {{1, 2}, {3, 4}, {5, 6}},
            {{7, 8}, {9, 10}, {11, 12}},
            {{13, 14}, {15, 16}, {17, 18}}
    };

    Point A = {0, 0}; // Starting point
    Point B = {2, 2}; // Destination point

    vector<vector<Direction>> dir(grid.size(), vector<Direction>(grid[0].size()));

    int minTimeRequired = minTime(grid, A, B, dir);
    cout << "Minimum time required: " << minTimeRequired << endl;

    printPath(dir, B);

    return 0;
}
