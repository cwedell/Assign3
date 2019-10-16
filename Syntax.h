#include "GenStack.h"
#include <iostream>

using namespace std;

class Syntax {
public:
  Syntax();
  Syntax(string filename);
  ~Syntax();
  bool findErrors();
private:
  GenStack<char> charStack = GenStack<char>(128); // store characters
  string file;
};
