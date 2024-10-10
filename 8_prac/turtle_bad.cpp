#include <iostream>
#include <queue>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

struct Cell {
    int distance;
    int timeUp;
    int timeRight;
    int timeDown;
    int timeLeft;
    int parentX;
    int parentY;
};

int main() {
    int n, m;
    cout << "Введите размер поля (n m): ";
    cin >> n >> m;

    srand(time(0)); // seed the random number generator

    Cell grid[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            grid[i][j].distance = INT_MAX;
            grid[i][j].timeUp = rand() % 10 + 1; // generate random time between 1 and 10
            grid[i][j].timeRight = rand() % 10 + 1;
            grid[i][j].timeDown = rand() % 10 + 1;
            grid[i][j].timeLeft = rand() % 10 + 1;
            grid[i][j].parentX = -1;
            grid[i][j].parentY = -1;
        }
    }

    int ax, ay, bx, by;
    cout << "Введите координаты точки A (x y): ";
    cin >> ax >> ay;
    cout << "Введите координаты точки B (x y): ";
    cin >> bx >> by;

    grid[ax][ay].distance = 0;

    queue<pair<int, int>> queue;
    queue.push({ax, ay});

    int dx[] = {-1, 0, 1, 0}; // up, right, down, left
    int dy[] = {0, 1, 0, -1}; // up, right, down, left

    while (!queue.empty()) {
        int x = queue.front().first;
        int y = queue.front().second;
        queue.pop();

        if (x == bx && y == by) {
            cout << "Минимальное время: " << grid[x][y].distance << endl;
        }

        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (newX >= 0 && newX < n && newY >= 0 && newY < m && (newX != x || newY != y)) {
                int newDistance = grid[x][y].distance + (i == 0 ? grid[x][y].timeUp : i == 1 ? grid[x][y].timeRight : i == 2 ? grid[x][y].timeDown : grid[x][y].timeLeft);

                if (newDistance < grid[newX][newY].distance) {
                    grid[newX][newY].distance = newDistance;
                    grid[newX][newY].parentX = x;
                    grid[newX][newY].parentY = y;
                    queue.push({newX, newY});
                }
            }
        }
    }

    // Output the square with all times and coordinates
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "(" << i << ", " << j << ") Up: " << grid[i][j].timeUp << " Right: " << grid[i][j].timeRight << " Down: " << grid[i][j].timeDown << " Left: " << grid[i][j].timeLeft << " Min: " << grid[i][j].distance << endl;
        }
        cout << endl;
    }

    // Output the path from point A to point B
    vector<pair<int, int>> path;
    int x = bx, y = by;
    while (x != ax || y != ay) {
        path.push_back({x, y});
        int newX = grid[x][y].parentX;
        int newY = grid[x][y].parentY;
        x = newX;
        y = newY;
    }
    path.push_back({ax, ay});
    reverse(path.begin(), path.end());
    cout << "Путь: ";
    for (int i = 0; i < path.size(); i++) {
        cout << "(" << path[i].first << ", " << path[i].second << ") ";
    }
    cout << endl;

    if (bx >= 0 && bx < n && by >= 0 && by < m) {
        cout << "Минимальное время: " << grid[bx][by].distance << endl;
    } else {
        cout << "Минимальное время: -1" << endl; // no path found
    }

    return 0;
}
