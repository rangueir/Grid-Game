#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include "Object.h"

// Function prototypes
template<typename T>
void detectObjects(std::vector<std::vector<T> >& grid, int x, int y, const int width, const int height, Object& p1, int& objectCount, std::vector<std::vector<bool> >& visited);

int s_to_int(const std::string& y);

bool is_notdigit(std::string arr);

#endif // FUNCTIONS_H 
