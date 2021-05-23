#ifndef NODE_H
#define NODE_H
#include <vector>
#include <string>
#include <cmath>
#include "Symbol.h"

class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class IdentifierNode;
class ExpressionNode;
class CoutStatementNode;
class IntegerNode;
class IdentifierNode;
class BinaryOperatorNode;
class IfStatmentNode;
class WhileStatementNode;


class Node {
public:
    virtual ~Node();
    virtual void Interpret() = 0;

private:
};


class StartNode: public Node{
public:
    StartNode(ProgramNode* n);
    ~StartNode();
    void Interpret();
private:
    ProgramNode* pn;
};


class ProgramNode: public Node{
public:
    ProgramNode(BlockNode* n);
    ~ProgramNode();
    void Interpret();
private:
    BlockNode* bn;
};




class StatementGroupNode: public Node {
public:
    StatementGroupNode();
    ~StatementGroupNode();
    void AddStatement(StatementNode* sn);
    void Interpret();
private:
    std::vector<StatementNode*> mStatementNodes;
};


class StatementNode: public Node {
public:
    ~StatementNode();
private:
};

class BlockNode: public StatementNode {
public:
    BlockNode(StatementGroupNode* n);
    ~BlockNode();
    void Interpret();
private:
    StatementGroupNode* sgn;
};


class DeclarationStatementNode: public StatementNode {
public:
    DeclarationStatementNode(IdentifierNode* n, ExpressionNode *asn);
    ~DeclarationStatementNode();
    void Interpret();
private:
    IdentifierNode* in;
    ExpressionNode* en;
};


class AssignmentStatementNode: public StatementNode {
public:
   AssignmentStatementNode(IdentifierNode* idn, ExpressionNode* exn); 
   ~AssignmentStatementNode();
   void Interpret();
    IdentifierNode* in;
    ExpressionNode* en;
};


class CoutStatementNode: public StatementNode{
public:
    CoutStatementNode(ExpressionNode* n);
    ~CoutStatementNode();
    void Interpret();
private:
    ExpressionNode* en;
};

class IfStatementNode: public StatementNode{
public:
    IfStatementNode(ExpressionNode* e, StatementNode* s1, StatementNode* s2);
    ~IfStatementNode();
    void Interpret();
private:
    ExpressionNode* en;
    StatementNode* sn1;
    StatementNode* sn2;
};

class WhileStatementNode: public StatementNode{
public:
    WhileStatementNode(ExpressionNode* e, StatementNode* s);
    ~WhileStatementNode();
    void Interpret();
private:
    ExpressionNode* en;
    StatementNode* sn;
};

class RepeatStatementNode: public StatementNode{
public:
    RepeatStatementNode(ExpressionNode* e, StatementNode* s);
    ~RepeatStatementNode();
    void Interpret();
private:
    ExpressionNode* en;
    StatementNode* sn;
};

class ExpressionNode{
public:
    ExpressionNode();
    virtual ~ExpressionNode();
    virtual int Evaluate() = 0;
private:
};


class IntegerNode: public ExpressionNode{
public:
    IntegerNode(int x);
    int Evaluate();
private:
    int mInteger;
};


class IdentifierNode: public ExpressionNode{
public:
    IdentifierNode(std::string label, SymbolTableClass* st);
    void DeclareVariable();
    void SetValue(int v);
    int GetIndex();
    int Evaluate();

private:
    std::string mLabel;
    SymbolTableClass* mSymbolTable;
    
};


class BinaryOperatorNode: public ExpressionNode{
public:
    BinaryOperatorNode(ExpressionNode* l, ExpressionNode* r);
    virtual ~BinaryOperatorNode();
protected:
    ExpressionNode* mLeft;
    ExpressionNode* mRight;
private:
};


class PlusNode: public BinaryOperatorNode{
public:
    PlusNode(ExpressionNode* l, ExpressionNode* r);
    int Evaluate();
private:
};


class MinusNode: public BinaryOperatorNode{
public:
    MinusNode(ExpressionNode* l, ExpressionNode* r);
    int Evaluate();
private:
};


class TimesNode: public BinaryOperatorNode{
public:
    TimesNode(ExpressionNode* l, ExpressionNode* r);
    int Evaluate();
private:
};


class DivideNode: public BinaryOperatorNode{
public:
    DivideNode(ExpressionNode* l, ExpressionNode* r);
    int Evaluate();
private:
};

class ExponentNode: public BinaryOperatorNode{
public:
    ExponentNode(ExpressionNode* l, ExpressionNode* r);
    int Evaluate();
private:
};

class LessNode: public BinaryOperatorNode{
public:
    LessNode(ExpressionNode* l, ExpressionNode* r);
    int Evaluate();
private:
};


class LessEqualNode: public BinaryOperatorNode{
public:
    LessEqualNode(ExpressionNode* l, ExpressionNode* r);
    int Evaluate();
private:
};


class GreaterNode: public BinaryOperatorNode{
public:
    GreaterNode(ExpressionNode* l, ExpressionNode* r);
    int Evaluate();
private:
};


class GreaterEqualNode: public BinaryOperatorNode{
public:
    GreaterEqualNode(ExpressionNode* l, ExpressionNode* r);
    int Evaluate();
private:
};


class EqualNode: public BinaryOperatorNode{
public:
    EqualNode(ExpressionNode* l, ExpressionNode* r);
    int Evaluate();
private:
};


class NotEqualNode: public BinaryOperatorNode{
public:
    NotEqualNode(ExpressionNode* l, ExpressionNode* r);
    int Evaluate();
private:
};

class AndNode: public BinaryOperatorNode{
public:
    AndNode(ExpressionNode* l, ExpressionNode* r);
    int Evaluate();
private:
};

class BitwiseAndNode: public BinaryOperatorNode{
public:
    BitwiseAndNode(ExpressionNode* l, ExpressionNode* r);
    int Evaluate();
private:
};

class OrNode: public BinaryOperatorNode{
public:
    OrNode(ExpressionNode* l, ExpressionNode* r);
    int Evaluate();
private:
};
#endif /*NODE_H*/