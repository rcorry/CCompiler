#include "scanner.h"
//#include "Symbol.h"
#include "Node.h"

class ParserClass {
public:
    ParserClass(ScannerClass *scanner, SymbolTableClass *table);
    StatementNode* Statement();
    StartNode* Start();
    StatementGroupNode* StatementGroup();
    DeclarationStatementNode* DeclarationStatement();
    void StartStatement();
    ProgramNode* ProgramStatement();
    BlockNode* BlockStatement();
    AssignmentStatementNode* AssignmentStatement();
    CoutStatementNode* CoutStatement();
    IfStatementNode* IfStatement();
    WhileStatementNode* WhileStatement();
    RepeatStatementNode* RepeatStatement();
    IdentifierNode* Identifier();
    ExpressionNode* ExpressionStatement();
    ExpressionNode* AndStatement();
    ExpressionNode* BitwiseAndStatement();
    ExpressionNode* OrStatement();
    ExpressionNode* RelationalStatement();
    ExpressionNode* PlusMinus();
    ExpressionNode* TimesDivide();
    ExpressionNode* Factor();
    IntegerNode* Integer();
    TokenClass Match(TokenType expectedType);

private:
    ScannerClass* mScanner;
    SymbolTableClass *mTable;

};