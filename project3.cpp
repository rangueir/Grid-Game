#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <ctime>


#include <sstream>
#include <cstdlib>
#include <cstring>

#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/FormEntry.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace std;
using namespace cgicc;


struct Object {
    string sequence;
    int x;
    int y;
    int centerX;
    int centerY;
    int size;
    char id;
};


template<typename T>
void detectObjects(vector<vector<T>>& grid, int x, int y, const int width, const int height, Object& p1, int& objectCount, vector<vector<bool>>& visited) {
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

int main() {

    Cgicc cgi;
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html>\n";
    cout << "<head>\n";
    cout << "<title>CPS 3525 Project 3</title>\n";

    //Script shows file upload section when button is clicked
    cout << "<script>";
    cout << "function myFunction() {";
    cout << "var x = document.getElementById('myDIV');";
    cout << "if (x.style.display === 'none') {x.style.display = 'block';} else {x.style.display = 'none';";
    cout << "}";
    cout << "}";
    cout << "</script>";
    
    cout << "<style>";
    cout << "#myDIV {display: none;}";
    cout << "body {font-family: Arial, sans-serif;margin: 0;padding: 0;background-color: #f2f2f2;}" << endl;
    cout << ".container {text-align: center;max-width: 800px;margin: 0 auto;margin-top: 20px;padding: 20px;background-color: #fff;border-radius: 8px;box-shadow: 0 0 10px rgba(0, 0, 0, 0.2);}" << endl;
    cout << ".center {margin-left: auto;margin-right: auto;text-align: center;}";
    cout << ".container h1 {text-align: center;}";
    cout << "</style>";

    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<div class='container'>";
    cout << "<h1>CPS 3525 Project 3</h1>\n";
    
    //Get text from textbox
    string input = cgi("userinput");

    string rows = cgi("rows");
    int numrows;
    int numcols;

    if(rows == ""){
        cout << "<font color='red'>You forgot to select number of rows...</font>" << endl;
    }else{
        if (is_notdigit(rows)) {
            cout << "<font color='blue'><b>" << rows << "</b></font> <font color='red'>Is not a number. Please enter a number...</font>" << endl;
        } else {
            numrows = s_to_int(rows);
        }
    }

    string cols = cgi("cols");

    if(cols == ""){
        cout << "<font color='red'>You forgot to select number of columns...</font>" << endl;
    }else{
        if (is_notdigit(cols)) {
            cout << "<font color='blue'><b>" << cols << "</b></font> <font color='red'>Is not a number. Please enter a number...</font>" << endl;
        } else {
            numcols = s_to_int(cols);
        }
    }

    Object p1;
    srand(time(0));
    vector<vector<char>> mdarray(numrows, vector<char>(numcols));
    for(int i = 0; i < numrows; i++){
        for(int j = 0; j < numcols; j++){
            
            mdarray[i][j] = rand() % ('z' - 'a' + 1) + 'a';
        }
    }
    
    //Display dimensions and grid
    cout << "Height: " << numrows << ", Width: " << numcols << "<br>";
    cout << "<br>";
    cout << "<table class='center'>";
    for(int i = 0; i < numrows; i++){
        cout << "<tr>";
        for(int j = 0; j < numcols; j++){
            
            cout << "<td>" << mdarray[i][j] << "</td>" ;
            
        }
        cout << "</tr>";
        //cout << "<br>";
    }
    cout << "</table>";
    
    vector<vector<char>> textGrid(mdarray.size());
    for (int i = 0; i < mdarray.size(); i++) {
        textGrid[i].resize(mdarray[i].size());
        for (int j = 0; j < mdarray[i].size(); j++) {
            textGrid[i][j] = static_cast<char>(mdarray[i][j]);
        }
    }
    cout << "<hr>";
    //Button to display hidden section
    cout << "<button onclick='myFunction()'>Click here to see data uploaded from file!</button>";
    cout << "<div id='myDIV'>";
    cout << "<br>";
    cout << "Height: " << numrows << ", Width: " << numcols << "<br>";
    cout << "<br>";
    
    vector<vector<float>> details;
    vector<vector<bool>> visited(mdarray.size(), vector<bool>(mdarray[0].size(), false));

    int objectCount = 1;
    cout << "<table class='center'>";
    for(int i = 0; i < numrows; i++){
        cout << "<tr>";
        for(int j = 0; j < numcols; j++){
            if (objectCount <= 9) {
                p1.id = static_cast<char>(objectCount + 48); // For numbers 0 to 9
            } else {
                p1.id = 'A' + (objectCount - 10);
            }
            if (!visited[i][j]) {
                bool match = true;
                for (int l = 0; l < input.size(); ++l) {
                    if (textGrid[i][j + l] != input[l]) {
                        match = false;
                        cout << "<td>"  << textGrid[i][j] << "</td>" << endl;
                        visited[i][j + l] = true;
                        break;
                    }else{
                        for(int k = 0; k < input.size(); ++k) {
                            if (textGrid[i][j + k] == input[k]) {
                                textGrid[i][j + k] = p1.id;
                                visited[i][j + k] = true;
                                
                                cout << "<td style='color:#FF0000'>" << textGrid[i][j + k] << "</td>" << endl;
                            }else{
                                break;
                            }
                        }
                        objectCount++;
                    }
                    
                    // If we reach the end of the row, move to the next row
                    if (j > numcols) {
                        ++i;
                        j = 0;
                    }
                    // If we reach the end of textGrid, break the loop
                    if (i > numrows) {
                        break;
                    }
                }
            }
        }
        cout << "</tr>";
    }
    cout << "</table>";
    cout << "</div>";
    cout << "</body>\n";
    cout << "</html>\n";
    return 0;
}