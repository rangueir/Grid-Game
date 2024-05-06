#ifndef GET_VALIDATE_INPUTS_H
#define GET_VALIDATE_INPUTS_H

#include <iostream>
#include <vector>
#include <string>
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h> // Include the necessary header file for Cgicc
#include "Object.h"
#include "functions.h"


using namespace std;
using namespace cgicc;

void processInputs(const string& game, const string& option, const Cgicc& cgi);

#endif // GET_VALIDATE_INPUTS_H