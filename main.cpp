#include "Syntax.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

int main(int c, char** argv) {
  bool userFinished = false;
  while(!userFinished) {
    string file;
    bool fileGood = false;
    while(!fileGood) { // check for existing file
      cout << "Please enter the filename:" << endl;
      cin >> file;
      ifstream test(file);
      if(!test) {
        cout << "Invalid file." << endl;
        test.close();
        continue;
      }
      test.close();
      fileGood = true;
    }
    Syntax fileCheck = Syntax(file);
    if(fileCheck.findErrors()) { // true if errors are found
      userFinished = true;
      break;
    }
    else {
      cout << "No syntax errors found. Analyze another file? (y/n)" << endl;
      string response;
      while(cin >> response) { // check for valid response
        if(response == "Y" || response == "y") {
          break;
        } else if(response == "N" || response == "n") {
          cout << "Goodbye!" << endl;
          goto endWhile; // exit while loop
        } else {
          cout << "Invalid response. Analyze another file? (y/n)" << endl;
        }
      }
      endWhile: ;
    }
  }
}
