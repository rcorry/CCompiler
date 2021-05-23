#ifndef SCANNER
#define SCANNER
#include "Token.h"
#include "StateMachine.h"
#include "debug.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class ScannerClass {

public:
    ScannerClass(const string &filename);
    ~ScannerClass();
    TokenClass GetNextToken();
    TokenClass PeekNextToken();
    int GetLineNumber();

private:
    ifstream mFin;
    int mLineNumber;
    int mHackNumber;

};


#endif //SCANNER
