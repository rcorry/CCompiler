#include "Token.h"

TokenClass::TokenClass(){
    MSG("Initializing Token Object");
    mType = IDENTIFIER_TOKEN;
    mLexeme = gTokenTypeNames[mType];
    CheckReserved();
}


TokenClass::TokenClass(TokenType type, const string &lexeme){
    MSG("Initializing Token Object");
    mType = type;
    mLexeme = lexeme;
    CheckReserved();
}

TokenType TokenClass::GetTokenType() const {
    return mType;
}

TokenClass::~TokenClass(){}

void TokenClass::CheckReserved(){
    string l = mLexeme;
    if(l == "void"){
        mType = VOID_TOKEN;
    } else if( l == "main"){
        mType = MAIN_TOKEN;
    } else if( l == "int"){
        mType = INT_TOKEN;
    } else if( l == "cout"){
        mType = COUT_TOKEN;
    } else if( l == "for"){
        mType = FOR_TOKEN;
    } else if( l == "if"){
        mType = IF_TOKEN;
    } else if( l == "while"){
        mType = WHILE_TOKEN;
    } else if( l == "else"){
        mType = ELSE_TOKEN;
    } else if( l == "repeat"){
        mType = REPEAT_TOKEN;
    } else if( l == "EOF"){
        mType = EOF_TOKEN;
    }
}

std::ostream & operator<<(std::ostream & out, const TokenClass & tc) {
    out.setf(ios::left);
    out << "Type: " << setw(15) << tc.GetTokenTypeName() <<
        "Lexeme: " << setw(15) << tc.GetLexeme();
    return out;
};