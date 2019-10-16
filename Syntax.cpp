#include "Syntax.h"
#include <iostream>
#include <fstream>

using namespace std;

Syntax::Syntax() {
  file = "";
}

Syntax::Syntax(string filename) {
  file = filename;
}

Syntax::~Syntax() {
}

bool Syntax::findErrors() {
  ifstream is (file);
  string line = "";
  int lineNum = 1;
  char c = '\0';
  char checker = '\0';
  bool inQuotes = false;
  bool errorFound = false;
  while(getline(is, line) && !errorFound) {
    for(int i = 0; i < line.length(); ++i) {
      c = line[i];
      if(c == '\"') { // check for strings
        inQuotes = !inQuotes;
      }
      if(!inQuotes) { // ignore if in string
        if(c == '(' || c == '[' || c == '{') { // push if left-facing
          charStack.push(c);
        }
        if(c == ')' || c == ']' || c == '}') { // pop if right-facing
          if(charStack.isEmpty()) { // unmatched right-facing character
            cout << "Reached end of file, unexpected " + c << endl;
            errorFound = true;
            goto endWhile; // exit while loop
          } else {
            checker = charStack.pop();
          }
          if((checker == '(' && c != ')') || (checker == '[' && c != ']') || (checker == '{' && c != '}')) { // left- and right-facing characters don't match
            cout << "Error on line " + to_string(lineNum) + ", expected match to " + checker + " and found " + c << endl;
            errorFound = true;
            goto endWhile; // exit while loop
          }
        }
      }
    }
    ++lineNum;
  }
  endWhile:
  if(!charStack.isEmpty() && !errorFound) { // unmatched left-facing character
    char unmatched = '\0';
    unmatched = charStack.pop();
    if(unmatched == '(') {
      cout << "Reached end of file, missing )" << endl;
    } else if(unmatched == '[') {
      cout << "Reached end of file, missing ]" << endl;
    } else if(unmatched == '{') {
      cout << "Reached end of file, missing }" << endl;
    } else if(unmatched == ')') {
      cout << "Reached end of file, unexpected )" << endl;
    } else if(unmatched == ']') {
      cout << "Reached end of file, unexpected ]" << endl;
    } else if(unmatched == '}') {
      cout << "Reached end of file, unexpected }" << endl;
    }
    errorFound = true;
  }
  is.close();
  if(errorFound) {
    return true;
  } else {
    return false;
  }
}
