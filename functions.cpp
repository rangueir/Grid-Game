#include "functions.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
void detectObjects(vector<vector<T> >& grid, int x, int y, const int width, const int height, Object& p1, int& objectCount, vector<vector<bool> >& visited) {
    visited[x][y] = true;
    grid[x][y] = p1.id;

    detectObjects(grid, x + 1, y, width, height, p1, objectCount, visited);
    return;
}

int s_to_int(const string& y) {
    return stoi(y);
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

bool isNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

void searchAndMarkPattern(vector<vector<char>>& textGrid, const string& input, int& objectCount, vector<vector<bool>>& visited, int numrows, int numcols, char count, int userinput) {

        cout << "<table class='center'>";
        // Loop through the grid
        for (int i = 0; i < numrows; i++) {
                for (int j = 0; j < numcols; j++) {
                        // Set object ID based on objectCount
                        if (objectCount <= 9) {
                                count = static_cast<char>(objectCount + 48); // For numbers 0 to 9
                        } else {
                                count = 'A' + (objectCount - 10);
                        }

                        // Check if the current cell has been visited
                        if (!visited[i][j]) {
                                bool match = true;

                                // Check if the pattern matches starting from (i, j)
                                for (int l = 0; l < input.size(); ++l) {
                                        if (textGrid[i][j + l] != input[l]) {
                                                match = false;
                                                cout << "<td>"  << textGrid[i][j] << "</td>" << endl;
                                                visited[i][j + l] = true;
                                                break;
                                        } else {
                                                // Mark the pattern cells and update objectCount
                                                for (int k = 0; k < input.size(); ++k) {
                                                if (textGrid[i][j + k] == input[k]) {
                                                        textGrid[i][j + k] = count;
                                                        visited[i][j + k] = true;
                                                        cout << "<td style='color:#FF0000'>" << textGrid[i][j + k] << "</td>" << endl;
                                                } else {
                                                        break;
                                                }
                                                }
                                                objectCount++;
                                        }
                                        
                                        // Handle boundary conditions
                                        if (j > numcols) {
                                                ++i;
                                                j = 0;
                                        }
                                        if (i > numrows) {
                                                break;
                                        }
                                }
                        }
                }
                cout << "</tr>";
        }
        cout << "</table>";
        cout << "<br>";
        cout << "Your guess is " << userinput;
        cout << "<br>";
        cout << "There are " << objectCount - 1 << ", " << input << " characters!";

        if(userinput == objectCount - 1){
                cout << "<br>";
                cout << "Congratulations! You were correct.";
        }else{
                cout << "<br>";
                cout << "Try Again...";
        }
        
}

void displayMatchingValuesAtSamePosition(const vector<vector<char>>& vec1, const vector<vector<char>>& vec2) {
    // Check if the vectors have the same size
    int countmatches = 0;

    cout << "<table class='center'>";

    for (size_t i = 0; i < vec1.size(); ++i) {
        cout << "<tr>";
        for (size_t j = 0; j < vec1[i].size(); ++j) {
            // Check if the values at the current position match
            if (vec1[i][j] == vec2[i][j]) {
                cout << "<td style='color:#0000FF; font-weight:bold;'>" << vec1[i][j] << "</td> ";
                countmatches++;
            } else {
                // Display the non-matching value in black color
                cout << "<td>" << vec1[i][j] << "</td> ";
            }
        }
        cout << "</tr>";
    }
    cout << "</table>";
    cout << "<br>";
    cout << "You matched " << countmatches << " characters!";
}