#include "scanner.h"

ScannerClass::ScannerClass(const string &filename){
    MSG("Initializing Scanner Object");
    mLineNumber = 1;
    mFin.open(filename.c_str(), ios::binary);
    if(mFin.is_open()){

    } else {
        cout << "ERROR OPENING FILE";
        exit(0);
    }
}

ScannerClass::~ScannerClass(){
    mFin.close();
}

TokenClass ScannerClass::GetNextToken(){
    MachineState currentState;
    TokenType correspondingTokenType;
    char c;
    string lexeme;
    StateMachineClass machine;

    do {
        c = mFin.get();
        if(c == '\n'){
            mLineNumber ++;
        }
        lexeme += c;
        currentState = machine.UpdateState(c, correspondingTokenType);
        if(currentState == START_STATE || currentState == EOF_STATE){
            lexeme = "";
        }
    }
    while(currentState != CANTMOVE_STATE);

    if(correspondingTokenType == BAD_TOKEN){
        std::cout << "BAD TOKEN: " << c << std::endl;
        exit(0);
    }

    mFin.unget();
    if(c == '\n'){
        mLineNumber --;
    }
    lexeme.pop_back();
    TokenClass tc(correspondingTokenType, lexeme);
    return tc;

}

TokenClass ScannerClass::PeekNextToken(){
    int currentLine = mLineNumber;
    std::streampos pos = mFin.tellg();
    TokenClass T = GetNextToken();
    if(!mFin){
        mFin.clear();
    }
    mFin.seekg(pos);
    mLineNumber = currentLine;
    return T;
}