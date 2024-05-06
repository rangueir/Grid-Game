#include "get_validate_inputs.h"
#include "functions.h"
#include "Object.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <utility>
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

void processInputs(const string& game, const string& option, const Cgicc& cgi){
    if (game == "count") {
        cout << "You selected the Counter game." << endl;
        if (option == "rows") {
            cout << "You started a randomized game." << endl;
            //Get text from textbox
            string input = cgi("charinput");
            string rows = cgi("rows");
            string intinput = cgi("intinput");
            int guess = s_to_int(intinput);
            int numrows;
            int numcols;

            if (isNumber(input)) {
                cout << "<br>";
                cout << "<font color='red'>Please only enter letters...</font>" << endl;
            } else {
                if(rows == ""){
                    cout << "<font color='red'>You forgot to select the number of rows...</font>" << "<br>" << endl;
                }else{
                    if (is_notdigit(rows)) {
                        cout << "<font color='blue'><b>" << rows << "</b></font> <font color='red'>Please enter a number...</font>" << "<br>" << endl;
                    } else {
                        numrows = s_to_int(rows);
                    }
                }

                string cols = cgi("cols");
                if(cols == ""){
                    cout << "<font color='red'>You forgot to select the number of columns...</font>" << "<br>" << endl;
                }else{
                    if (is_notdigit(cols)) {
                        cout << "<font color='blue'><b>" << cols << "</b></font> <font color='red'>Please enter a number...</font>" << "<br>" << endl;
                    } else {
                        numcols = s_to_int(cols);
                    }
                }

                Object p1;
                char counter;
                srand(time(0));
                vector<vector<char> > mdarray(numrows, vector<char>(numcols));
                for(int i = 0; i < numrows; i++){
                    for(int j = 0; j < numcols; j++){
                        
                        mdarray[i][j] = rand() % ('z' - 'a' + 1) + 'a';
                    }
                }
                
                //Display dimensions and grid
                cout << "<br>";
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
                
                vector<vector<char> > textGrid(mdarray.size());
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
                
                vector<vector<float> > details;
                vector<vector<bool> > visited(mdarray.size(), vector<bool>(mdarray[0].size(), false));

                int objectCount = 1;
                searchAndMarkPattern(textGrid, input, objectCount, visited, numrows, numcols, counter, guess);
            }
        }
        else if (option == "upload"){

            cout << "You started a pregen game." << endl;
            string input = cgi("ucharinput");
            string file;
            string uintinput = cgi("uintinput");
            if (isNumber(input)) {
                cout << "<br>";
                cout << "<font color='red'>Please only enter letters...</font>" << endl;
            } else {
                int fguess = s_to_int(uintinput);
                const_file_iterator fileupload = cgi.getFile("loadfile");
                
                //Save data from file as string
                string filedata = fileupload -> getData();
                string filedim = filedata;

                int flength = filedata.size();
                
                //This is all very similar to the first part of the assignment
                Object p2;
                char fcounter;
                for(int i = 0; i < flength; i++){
                    if(filedata[i] == ','){
                        filedata[i] = ' ';
                    }else if(filedata[i] == '\n'){
                        break;
                    }
                }

                for(int i = 4; i < flength; i++){
                    if(filedata[i]=='\n' || filedata[i]==' '){
                        continue;
                    }
                    p2.sequence += filedata[i]; // Append character to p2.sequence
                }
                
                stringstream ss2(filedim);
                vector<int> g;
                string filetoken;
                while (getline(ss2, filetoken, ',')) {
                    int value;
                    std::istringstream(filetoken) >> value;
                    g.push_back(value);
                }

                p2.x = g[0];
                p2.y = g[1];

                vector<vector<char>> farray(p2.x + 1, vector<char>(p2.y + 1));
                cout << "<br>";
                cout << "Height: " << p2.x << ", Width: " << p2.y << "<br>";
                cout << "<br>";
                int l = 0;
                for(int i = 0; i <= p2.x; ++i){
                    for(int j = 0; j <= p2.y; ++j){
                        
                        farray[i][j] = p2.sequence[l];
                        
                        l++;
                    }
                }
                
                for(int i = 0; i <= p2.x; i++){
                    for(int j = 0; j <= p2.y; j++){

                        cout << farray[i][j] << endl;
                        
                    }
                    cout << "<br>";
                }

                vector<vector<char>> fileGrid(farray.size());
                for (int i = 0; i < farray.size(); i++) {
                    fileGrid[i].resize(farray[i].size());
                    for (int j = 0; j < farray[i].size(); j++) {
                        fileGrid[i][j] = static_cast<char>(farray[i][j]);
                    }
                }
                
                vector<vector<bool>> fvisited(farray.size(), vector<bool>(farray[0].size(), false));

                int fobjectCount = 1;
                searchAndMarkPattern(fileGrid, input, fobjectCount, fvisited, p2.x, p2.y, fcounter, fguess);
            }
        }
    }
    else if (game == "match"){
        cout << "You selected the Match game." << endl;
        cout << "<br>";
        string matchrows = cgi("matchrows");
        int mnumrows;
        int mnumcols;

        if(matchrows == ""){
            cout << "<font color='red'>You forgot to select the number of rows...</font>" << "<br>" << endl;
        }else{
            if (is_notdigit(matchrows)) {
                cout << "<font color='blue'><b>" << matchrows << "</b></font> <font color='red'>Please enter a number...</font>" << "<br>" << endl;
            } else {
                mnumrows = s_to_int(matchrows);
            }
        }

        string matchcols = cgi("matchcols");

        if(matchcols == ""){
            cout << "<font color='red'>You forgot to select the number of columns...</font>" << "<br>" << endl;
        }else{
            if (is_notdigit(matchcols)) {
                cout << "<font color='blue'><b>" << matchcols << "</b></font> <font color='red'>Please enter a number...</font>" << "<br>" << endl;
            } else {
                mnumcols = s_to_int(matchcols);
            }
        }

        char counter;
        srand(time(0));
        vector<vector<char> > mdarray(mnumrows, vector<char>(mnumcols));
        for(int i = 0; i < mnumrows; i++){
            for(int j = 0; j < mnumcols; j++){
                
                mdarray[i][j] = rand() % ('z' - 'a' + 1) + 'a';
            }
        }
        
        //Display dimensions and grid
        cout << "Height: " << mnumrows << ", Width: " << mnumcols << "<br>";
        cout << "<br>";
        cout << "<table class='center'>";
        for(int i = 0; i < mnumrows; i++){
            cout << "<tr>";
            for(int j = 0; j < mnumcols; j++){
                
                cout << "<td>" << mdarray[i][j] << "</td>";
                
            }
            cout << "</tr>";
            //cout << "<br>";
        }
        cout << "</table>";
        
        vector<vector<char> > textGrid(mdarray.size());
        for (int i = 0; i < mdarray.size(); i++) {
            textGrid[i].resize(mdarray[i].size());
            for (int j = 0; j < mdarray[i].size(); j++) {
                textGrid[i][j] = static_cast<char>(mdarray[i][j]);
            }
        }
        /*-----------------------------------------------------------------------------------------------------*/
        cout << "<hr>";
        string matchfile;
        const_file_iterator mfileupload = cgi.getFile("matchloadfile");
        
        //Save data from file as string
        string mfiledata = mfileupload -> getData();
        string mfiledim = mfiledata;

        int mlength = mfiledata.size();
        
        Object p3;
        char mcounter;
        for(int i = 0; i < mlength; i++){
            if(mfiledata[i] == ','){
                mfiledata[i] = ' ';
            }else if(mfiledata[i] == '\n'){
                break;
            }
        }

        for(int i = 4; i < mlength; i++){
            if(mfiledata[i]=='\n' || mfiledata[i]==' '){
                continue;
            }
            p3.sequence += mfiledata[i]; // Append character to p3.sequence
        }
        
        stringstream ss3(mfiledim);
        vector<int> h;
        string mfiletoken;
        while (getline(ss3, mfiletoken, ',')) {
            int value;
            std::istringstream(mfiletoken) >> value;
            h.push_back(value);
        }

        p3.x = h[0] + 1;
        p3.y = h[1] - 1;

        vector<vector<char>> matcharray(p3.x + 1, vector<char>(p3.y + 1));

        cout << "Height: " << p3.x - 1 << ", Width: " << p3.y + 1  << "<br>";
        cout << "<br>";
        int r = 0;
        for(int i = 0; i <= p3.x; ++i){
            for(int j = 0; j <= p3.y; ++j){
                
                matcharray[i][j] = p3.sequence[r];
                
                r++;
            }
        }
        cout << "<table class='center'>";
        for(int i = 0; i <= p3.x; ++i){
            cout << "<tr>";
            for(int j = 0; j <= p3.y; ++j){

                cout << "<td>" << matcharray[i][j] << "</td>";
                
            }
            cout << "<tr>";
            //cout << "<br>";
        }
        cout << "</table>";
        cout << "<br>";

        vector<vector<char>> mfileGrid(matcharray.size());
        for (int i = 0; i < matcharray.size(); i++) {
            mfileGrid[i].resize(matcharray[i].size());
            for (int j = 0; j < matcharray[i].size(); j++) {
                mfileGrid[i][j] = static_cast<char>(matcharray[i][j]);
            }
        }

        if(mnumrows == p3.x - 1 && mnumcols == p3.y + 1){
            displayMatchingValuesAtSamePosition(textGrid, mfileGrid);
        }else{
            cout << "<br>";
            cout << "<font color='red'>Your grid must be the same size as the computer's grid.</font>" << endl;
        }

        
    }
}
