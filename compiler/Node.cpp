#include "Node.h"

Node::~Node(){}

StartNode::StartNode(ProgramNode* n){
    pn = n;
}

StartNode::~StartNode(){
    delete(pn);
}

void StartNode::Interpret(){
    pn->Interpret();
}

ProgramNode::ProgramNode(BlockNode* n){
    bn = n;
}

ProgramNode::~ProgramNode(){
    delete(bn);
}

void ProgramNode::Interpret(){
    bn->Interpret();
}

BlockNode::BlockNode(StatementGroupNode* n){
    sgn = n;
}

BlockNode::~BlockNode(){
    delete(sgn);
}

void BlockNode::Interpret(){
    sgn->Interpret();
}

StatementGroupNode::StatementGroupNode(){

}

StatementGroupNode::~StatementGroupNode(){
    for(int i=0; i<(int)mStatementNodes.size(); i++){
        delete mStatementNodes[i];
    }
}

void StatementGroupNode::AddStatement(StatementNode* sn){
    mStatementNodes.push_back(sn);
}

void StatementGroupNode::Interpret(){
    for(int i=0; i<(int)mStatementNodes.size(); i++){
        mStatementNodes[i]->Interpret();
    }
}

StatementNode::~StatementNode(){}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* n, ExpressionNode *a){
    in = n;
    en = a;
}

DeclarationStatementNode::~DeclarationStatementNode(){
    delete(in);
    delete(en);
}

void DeclarationStatementNode::Interpret(){
    in->DeclareVariable();
    if(en != NULL){
        in->SetValue(en->Evaluate());
    }
}
AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* idn, ExpressionNode* exn){
    in = idn;
    en = exn;
}

AssignmentStatementNode::~AssignmentStatementNode(){
    delete(in);
    delete(en);
}

void AssignmentStatementNode::Interpret(){
    in->SetValue(en->Evaluate());
}


CoutStatementNode::CoutStatementNode(ExpressionNode* n){
    en = n;
}

CoutStatementNode::~CoutStatementNode(){
    delete(en);
}

void CoutStatementNode::Interpret(){
    std::cout << en->Evaluate() << std::endl;
}

IfStatementNode::IfStatementNode(ExpressionNode* e, StatementNode* s1, StatementNode* s2){
    en = e;
    sn1 = s1;
    sn2 = s2;
}
IfStatementNode::~IfStatementNode(){
    delete(en);
    delete(sn1);
    delete(sn2);
}
void IfStatementNode::Interpret(){
    if(en->Evaluate() != 0){
        sn1->Interpret();
    } else if (sn2 != NULL){
        sn2->Interpret();
    }
}

WhileStatementNode::WhileStatementNode(ExpressionNode* e, StatementNode* s){
    en = e;
    sn = s;
}
WhileStatementNode::~WhileStatementNode(){
    delete(en);
    delete(sn);
}
void WhileStatementNode::Interpret(){
    while(en->Evaluate() != 0){
        sn->Interpret();
    }
}

RepeatStatementNode::RepeatStatementNode(ExpressionNode* e, StatementNode* s){
    en = e;
    sn = s;
}
RepeatStatementNode::~RepeatStatementNode(){
    delete(en);
    delete(sn);
}
void RepeatStatementNode::Interpret(){
    for(int i=0; i<en->Evaluate(); i++){
        sn->Interpret();
    }
}

ExpressionNode::ExpressionNode(){}

ExpressionNode::~ExpressionNode(){}

IntegerNode::IntegerNode(int x){
    mInteger = x;
}

int IntegerNode::Evaluate(){
    return mInteger;
}

IdentifierNode::IdentifierNode(std::string label, SymbolTableClass* st){
    mLabel = label;
    mSymbolTable = st;
}

void IdentifierNode::DeclareVariable(){
    mSymbolTable->AddEntry(mLabel);
}

void IdentifierNode::SetValue(int v){
    mSymbolTable->SetValue(mLabel, v);
}

int IdentifierNode::GetIndex(){
    return mSymbolTable->GetIndex(mLabel);
}

int IdentifierNode::Evaluate(){
    return mSymbolTable->GetValue(mLabel);
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* l, ExpressionNode* r){
    mLeft = l;
    mRight = r;
}

BinaryOperatorNode::~BinaryOperatorNode(){
    delete(mLeft);
    delete(mRight);
}

PlusNode::PlusNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right){
}

int PlusNode::Evaluate(){
    return mLeft->Evaluate() + mRight->Evaluate();
}

MinusNode::MinusNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right){
}

int MinusNode::Evaluate(){
    return mLeft->Evaluate() - mRight->Evaluate();
}

TimesNode::TimesNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right){
}

int TimesNode::Evaluate(){
    return mLeft->Evaluate() * mRight->Evaluate();
}

DivideNode::DivideNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right){
}

int DivideNode::Evaluate(){
    return mLeft->Evaluate() / mRight->Evaluate();
}

ExponentNode::ExponentNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right){
}

int ExponentNode::Evaluate(){
    return pow(mLeft->Evaluate() , mRight->Evaluate());
}

LessNode::LessNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right){
}

int LessNode::Evaluate(){
    return mLeft->Evaluate() < mRight->Evaluate();
}

LessEqualNode::LessEqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right){
}

int LessEqualNode::Evaluate(){
    return mLeft->Evaluate() <= mRight->Evaluate();
}

GreaterNode::GreaterNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right){
}

int GreaterNode::Evaluate(){
    return mLeft->Evaluate() > mRight->Evaluate();
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right){
}

int GreaterEqualNode::Evaluate(){
    return mLeft->Evaluate() >= mRight->Evaluate();
}

EqualNode::EqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right){
}

int EqualNode::Evaluate(){
    return mLeft->Evaluate() == mRight->Evaluate();
}

NotEqualNode::NotEqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right){
}

int NotEqualNode::Evaluate(){
    return mLeft->Evaluate() != mRight->Evaluate();
}

AndNode::AndNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right){
}

int AndNode::Evaluate(){
    return (mLeft->Evaluate() && mRight->Evaluate());
}

BitwiseAndNode::BitwiseAndNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right){
}

int BitwiseAndNode::Evaluate(){
    return (mLeft->Evaluate() & mRight->Evaluate());
}

OrNode::OrNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right){
}

int OrNode::Evaluate(){
    return (mLeft->Evaluate() || mRight->Evaluate());
}