#ifndef TOKEN
#define TOKEN
#include "debug.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

enum TokenType {
	// Reserved Words:
	VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN, FOR_TOKEN, IF_TOKEN, WHILE_TOKEN, ELSE_TOKEN, REPEAT_TOKEN, 
	// Relational Operators:
    LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN, EQUAL_TOKEN, NOTEQUAL_TOKEN, AND_TOKEN, OR_TOKEN, BITAND_TOKEN,
	// Other Operators:
    INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN, TIMES_TOKEN, DIVIDE_TOKEN, EXPONENT_TOKEN,
	// Other Characters:
	SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN,
    RCURLY_TOKEN,
	// Other Token Types:
	IDENTIFIER_TOKEN, INTEGER_TOKEN, 
	BAD_TOKEN, EOF_TOKEN
};

const std::string gTokenTypeNames[] = {
	"VOID", "MAIN", "INT", "COUT", "FOR", "IF", "WHILE", "ELSE", "REPEAT",
    "LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL", "NOTEQUAL", "AND", "OR", "BITAND",
	"INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", "DIVIDE",
	"SEMICOLON", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
	"IDENTIFIER", "INTEGER", 
	"BAD", "EOF"
};

class TokenClass {

public:
    TokenClass();
    TokenClass(TokenType type, const std::string &lexeme);
    ~TokenClass();
    TokenType GetTokenType() const;
    std::string GetLexeme() const {return mLexeme;};
    const std::string & GetTokenTypeName() const   
        { return gTokenTypeNames[mType];};
    void CheckReserved();
    static const std::string & GetTokenTypeName(TokenType type)
        { return gTokenTypeNames[type];};

private:
    TokenType mType;
    std::string mLexeme;
};

std::ostream & operator<<(std::ostream & out, const TokenClass & tc);

#endif //TOKEN