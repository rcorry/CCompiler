#include "StateMachine.h"

StateMachineClass::StateMachineClass(){
    MSG("Initializing State Machine Object");
    mCurrentState = START_STATE;
    for(int i=0; i<LAST_STATE; i++){
        for(int j=0; j<LAST_STATE; j++){
            mLegalMoves[i][j] = CANTMOVE_STATE;
        }
    }
    mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
    mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;
    mLegalMoves[START_STATE][NEWLINE_CHAR] = START_STATE;    mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;

    mLegalMoves[START_STATE][LESS_CHAR] = LESS_STATE;
    mLegalMoves[LESS_STATE][EQUAL_CHAR] = LESSEQUAL_STATE;
    mLegalMoves[LESS_STATE][LESS_CHAR] = INSERTION_STATE;

    mLegalMoves[START_STATE][GREATER_CHAR] = GREATER_STATE;
    mLegalMoves[GREATER_STATE][EQUAL_CHAR] = GREATEREQUAL_STATE;

    mLegalMoves[START_STATE][AND_CHAR] = BITAND_STATE;
    mLegalMoves[BITAND_STATE][AND_CHAR] = AND_STATE;
    mLegalMoves[START_STATE][OR_CHAR] = BITOR_STATE;
    mLegalMoves[BITOR_STATE][OR_CHAR] = OR_STATE;

    mLegalMoves[START_STATE][EQUAL_CHAR] = ASSIGNMENT_STATE;
    mLegalMoves[ASSIGNMENT_STATE][EQUAL_CHAR] = EQUAL_STATE;
    mLegalMoves[START_STATE][NOT_CHAR] = NOT_STATE;
    mLegalMoves[NOT_STATE][EQUAL_CHAR] = NOTEQUAL_STATE;

    mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
    mLegalMoves[PLUS_STATE][EQUAL_CHAR] = PLUSEQUAL_STATE;

    mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;
    mLegalMoves[MINUS_STATE][EQUAL_CHAR] = MINUSEQUAL_STATE;

    mLegalMoves[START_STATE][TIMES_CHAR] = TIMES_STATE;
    mLegalMoves[TIMES_STATE][EQUAL_CHAR] = TIMESEQUAL_STATE;
    mLegalMoves[TIMES_STATE][TIMES_CHAR] = EXPONENT_STATE;

    mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;
    mLegalMoves[DIVIDE_STATE][EQUAL_CHAR] = DIVIDEEQUAL_STATE;

    mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;
    mLegalMoves[START_STATE][LPAREN_CHAR] = LPAREN_STATE;
    mLegalMoves[START_STATE][RPAREN_CHAR] = RPAREN_STATE;
    mLegalMoves[START_STATE][LCURLY_CHAR] = LCURLY_STATE;
    mLegalMoves[START_STATE][RCURLY_CHAR] = RCURLY_STATE;
    mLegalMoves[START_STATE][EOF_CHAR] = EOF_STATE;
    mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
    mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = SINGLE_LINE_COMMENT_STATE;

    for(int i=0; i<LAST_STATE; i++){
        mLegalMoves[SINGLE_LINE_COMMENT_STATE][i] = SINGLE_LINE_COMMENT_STATE;
    }
    mLegalMoves[SINGLE_LINE_COMMENT_STATE][NEWLINE_CHAR] = START_STATE;

    mLegalMoves[DIVIDE_STATE][TIMES_CHAR] = BLOCK_COMMENT_STATE;
    for(int i=0; i<LAST_STATE; i++){
        mLegalMoves[BLOCK_COMMENT_STATE][i] = BLOCK_COMMENT_STATE;
    }

    mLegalMoves[BLOCK_COMMENT_STATE][TIMES_CHAR] = EXIT_STATE;
    for(int i=0; i<LAST_STATE; i++){
        mLegalMoves[EXIT_STATE][i] = BLOCK_COMMENT_STATE;
    }
    mLegalMoves[EXIT_STATE][TIMES_CHAR] = EXIT_STATE;
    mLegalMoves[EXIT_STATE][DIVIDE_CHAR] = START_STATE;





    for(int i=0; i<LAST_STATE; i++){
        mCorrespondingTokenTypes[i] = BAD_TOKEN;
    }
    mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
    mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
    mCorrespondingTokenTypes[LESS_STATE] = LESS_TOKEN;
    mCorrespondingTokenTypes[GREATER_STATE] = GREATER_TOKEN;
    mCorrespondingTokenTypes[LESSEQUAL_STATE] = LESSEQUAL_TOKEN;
    mCorrespondingTokenTypes[GREATEREQUAL_STATE] = GREATEREQUAL_TOKEN;
    mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
    mCorrespondingTokenTypes[NOTEQUAL_STATE] = NOTEQUAL_TOKEN;
    mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
    mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
    mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
    mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
    mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
    mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
    mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
    mCorrespondingTokenTypes[LPAREN_STATE] = LPAREN_TOKEN;
    mCorrespondingTokenTypes[RPAREN_STATE] = RPAREN_TOKEN;
    mCorrespondingTokenTypes[LCURLY_STATE] = LCURLY_TOKEN;
    mCorrespondingTokenTypes[RCURLY_STATE] = RCURLY_TOKEN;
    mCorrespondingTokenTypes[EOF_STATE] = EOF_TOKEN;
    mCorrespondingTokenTypes[EQUAL_STATE] = EQUAL_TOKEN;
    mCorrespondingTokenTypes[AND_STATE] = AND_TOKEN;
    mCorrespondingTokenTypes[OR_STATE] = OR_TOKEN;
    mCorrespondingTokenTypes[EXPONENT_STATE] = EXPONENT_TOKEN;
    mCorrespondingTokenTypes[BITAND_STATE] = BITAND_TOKEN;

}

bool isdigit(char character){
    if(character >= '0' and character <= '9'){
        return true;
    }
    return false;
}

bool isalpha(char character){
    if((character >= 'A' and character <= 'Z') || (character >= 'a' and character <= 'z')){
        return true;
    }
    return false;
}

MachineState StateMachineClass::UpdateState(char currentCharacter, TokenType & correspondingTokenType){
    CharacterType charType = BAD_CHAR;

    if(isdigit(currentCharacter))
        {charType = DIGIT_CHAR;}
    if(isalpha(currentCharacter))
        {charType = LETTER_CHAR;}
    if(currentCharacter == ' ')
        {charType = WHITESPACE_CHAR;}
    if(currentCharacter == 9)
        {charType = WHITESPACE_CHAR;}
    if(currentCharacter == '\n')
        {charType = NEWLINE_CHAR;}
    if(currentCharacter == '+')
        {charType = PLUS_CHAR;}
    if(currentCharacter == '-')
        {charType = MINUS_CHAR;}
    if(currentCharacter == '*')
        {charType = TIMES_CHAR;}
    if(currentCharacter == '=')
        {charType = EQUAL_CHAR;}
    if(currentCharacter == '!')
        {charType = NOT_CHAR;}
    if(currentCharacter == '&')
        {charType = AND_CHAR;}
    if(currentCharacter == '|')
        {charType = OR_CHAR;}
    if(currentCharacter == '(')
        {charType = LPAREN_CHAR;}
    if(currentCharacter == ')')
        {charType = RPAREN_CHAR;}
    if(currentCharacter == '{')
        {charType = LCURLY_CHAR;}
    if(currentCharacter == '}')
        {charType = RCURLY_CHAR;}
    if(currentCharacter == ';')
        {charType = SEMICOLON_CHAR;}
    if(currentCharacter == '<')
        {charType = LESS_CHAR;}
    if(currentCharacter == '>')
        {charType = GREATER_CHAR;}
    if(currentCharacter == '/')
        {charType = DIVIDE_CHAR;}
    if(currentCharacter == EOF)
        {charType = EOF_CHAR;}

    correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
    mCurrentState = mLegalMoves[mCurrentState][charType];
    return mCurrentState;
}