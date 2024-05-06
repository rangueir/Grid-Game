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

#include "Object.h"
#include "functions.h"
#include "get_validate_inputs.h"

using namespace std;
using namespace cgicc;

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
    cout << "body {font-family: Arial, sans-serif;margin: 0;padding: 0;background-color: #302222;}" << endl;
    cout << ".container {text-align: center;max-width: 800px;margin: 0 auto;margin-top: 20px;padding: 20px;background-color: #fff;border-radius: 8px;box-shadow: 0 0 10px rgba(0, 0, 0, 0.2);}" << endl;
    cout << ".center {margin-left: auto;margin-right: auto;text-align: center;}";
    cout << ".container h1 {text-align: center;}";
    cout << "</style>";

    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<div class='container'>";
    cout << "<center><img src='../CPS3525/gridgame.png' alt='gridgame'></center>\n";
    cout << "<br>";
    
    string game = cgi("game");
    string option = cgi("option");

    processInputs(game, option, cgi);
    
    
    cout << "<hr>";

    cout << "</div>";
    cout << "</body>\n";
    cout << "</html>\n";
    return 0;
}
