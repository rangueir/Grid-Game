#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include "Object.h"

// Function prototypes
template<typename T>
void detectObjects(std::vector<std::vector<T> >& grid, int x, int y, const int width, const int height, Object& p1, int& objectCount, std::vector<std::vector<bool> >& visited);

void searchAndMarkPattern(std::vector<std::vector<char>>& textGrid, const std::string& input, int& objectCount, std::vector<std::vector<bool>>& visited, int numrows, int numcols, char count, int userinput);

void displayMatchingValuesAtSamePosition(const std::vector<std::vector<char>>& vec1, const std::vector<std::vector<char>>& vec2);

int s_to_int(const std::string& y);

bool is_notdigit(std::string arr);

bool isNumber(const std::string& str);

#endif // FUNCTIONS_H 
