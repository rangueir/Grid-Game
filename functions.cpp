#include "functions.h"
#include <string>

template<typename T>
void detectObjects(vector<vector<T> >& grid, int x, int y, const int width, const int height, Object& p1, int& objectCount, vector<vector<bool> >& visited) {
    visited[x][y] = true;
    grid[x][y] = p1.id;

    detectObjects(grid, x + 1, y, width, height, p1, objectCount, visited); // right
    return;
}

int s_to_int(const std::string& y) {
    return std::stoi(y);
}

bool is_notdigit(string arr)
{
        for (int k = 0; k < arr.length(); k++) {
                if ((int)arr[k]<(int)'0' ||
                        (int)arr[k]>(int)'9') {
                        return true;
                }
        }
        return false;
}
