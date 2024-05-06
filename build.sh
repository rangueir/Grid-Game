# Compilation
g++ -c -Wall -Wextra -std=c++11 functions.cpp get_validate_inputs.cpp main.cpp

# Linking
g++ -o main functions.o get_validate_inputs.o main.o -lcgicc

chmod 705 main
