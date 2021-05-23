#include "Parser.h"

ParserClass::ParserClass(ScannerClass *scanner, SymbolTableClass *table){
    mScanner = scanner;
    mTable = table;
}

StartNode * ParserClass::Start(){
	ProgramNode *pn = ProgramStatement();
	Match(EOF_TOKEN);
	StartNode *sn = new StartNode(pn);
	return sn;
}

TokenClass ParserClass::Match(TokenType expectedType)
{
	TokenClass currentToken = mScanner->GetNextToken();
	if(currentToken.GetTokenType() != expectedType)
	{
		cerr << "Error in ParserClass::Match. " << endl;
		cerr << "Expected token type " << 
			TokenClass:: GetTokenTypeName(expectedType) << 
            ", but got type " << currentToken.GetTokenTypeName() << endl;
		exit(1);
	}
	MSG("\tSuccessfully matched Token Type: " << 
		currentToken.GetTokenTypeName() << ". Lexeme: \"" << 
		currentToken.GetLexeme() << "\"");
	return currentToken; // the one we just processed
}

StatementGroupNode* ParserClass::StatementGroup(){
	StatementGroupNode *sgn = new StatementGroupNode();
	while(true){
		StatementNode *sn = Statement();
		if(sn==NULL){
			return sgn;
		}
		sgn->AddStatement(sn);
	}
}

StatementNode* ParserClass::Statement(){
	TokenClass tc = mScanner->PeekNextToken();
	TokenType tt = tc.GetTokenType();
	if(tt == INT_TOKEN){
		DeclarationStatementNode *dsn = DeclarationStatement();
		return dsn;
	}
	if(tt == IDENTIFIER_TOKEN){
		AssignmentStatementNode *asn = AssignmentStatement();
		return asn;
	}
	if(tt == COUT_TOKEN){
		CoutStatementNode *csn = CoutStatement();
		return csn;
	}
	if(tt == IF_TOKEN){
		IfStatementNode *isn = IfStatement();
		return isn;
	}
	if(tt == WHILE_TOKEN){
		WhileStatementNode *wsn = WhileStatement();
		return wsn;
	}
	if(tt == REPEAT_TOKEN){
		RepeatStatementNode *rsn = RepeatStatement();
		return rsn;
	}
	return NULL;
}

DeclarationStatementNode* ParserClass::DeclarationStatement(){
	//DeclarationStatement-> INT_TOKEN <Identifier> SEMICOLON_TOKEN
	Match(INT_TOKEN);
	IdentifierNode *in = Identifier();
	TokenClass tc = mScanner->PeekNextToken();
	TokenType tt = tc.GetTokenType();
	if(tt==ASSIGNMENT_TOKEN){
		Match(ASSIGNMENT_TOKEN);
		ExpressionNode *en = ExpressionStatement();
		Match(SEMICOLON_TOKEN);
		DeclarationStatementNode *dsn = new DeclarationStatementNode(in, en);
		return dsn;
	}
	Match(SEMICOLON_TOKEN);
	DeclarationStatementNode *dsn = new DeclarationStatementNode(in, NULL);
	return dsn;
}
//NEEDS WORK
IdentifierNode* ParserClass::Identifier(){
	TokenClass tc = Match(IDENTIFIER_TOKEN);
	IdentifierNode *in = new IdentifierNode(tc.GetLexeme(), mTable);
	return in;
}

AssignmentStatementNode* ParserClass::AssignmentStatement(){
	IdentifierNode *in = Identifier();
	Match(ASSIGNMENT_TOKEN);
	ExpressionNode *en = ExpressionStatement();
	Match(SEMICOLON_TOKEN);
	AssignmentStatementNode *asn = new AssignmentStatementNode(in, en);
	return asn;
}

CoutStatementNode* ParserClass::CoutStatement(){
	Match(COUT_TOKEN);
	Match(INSERTION_TOKEN);
	ExpressionNode *en = ExpressionStatement();
	Match(SEMICOLON_TOKEN);
	CoutStatementNode *cn = new CoutStatementNode(en);
	return cn;
}

IfStatementNode* ParserClass::IfStatement(){
	Match(IF_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode *en = ExpressionStatement();
	Match(RPAREN_TOKEN);

	TokenClass tc = mScanner->PeekNextToken();
	TokenType tt = tc.GetTokenType();
	if(tt == LCURLY_TOKEN){
		BlockNode *bn = BlockStatement();
		IfStatementNode* isn = new IfStatementNode(en, bn, NULL);
		return isn;
	} else {
		StatementNode *sn1 = Statement();
		tc = mScanner->PeekNextToken();
		tt = tc.GetTokenType();
		if(tt==ELSE_TOKEN){
			Match(ELSE_TOKEN);
			StatementNode *sn2 = Statement();
			IfStatementNode* isn = new IfStatementNode(en, sn1, sn2);
			return isn;
		}

		IfStatementNode* isn = new IfStatementNode(en,sn1, NULL);
		return isn;
	}
}

WhileStatementNode* ParserClass::WhileStatement(){
	Match(WHILE_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode *en = ExpressionStatement();
	Match(RPAREN_TOKEN);

	TokenClass tc = mScanner->PeekNextToken();
	TokenType tt = tc.GetTokenType();
	if(tt == LCURLY_TOKEN){
		BlockNode *bn = BlockStatement();
		WhileStatementNode* wsn = new WhileStatementNode(en, bn);
		return wsn;
	} else {
		StatementNode *sn = Statement();
		WhileStatementNode *wsn = new WhileStatementNode(en, sn);
		return wsn;
	}
}

RepeatStatementNode* ParserClass::RepeatStatement(){
	Match(REPEAT_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode *en = ExpressionStatement();
	Match(RPAREN_TOKEN);

	TokenClass tc = mScanner->PeekNextToken();
	TokenType tt = tc.GetTokenType();
	if(tt == LCURLY_TOKEN){
		BlockNode *bn = BlockStatement();
		RepeatStatementNode* rsn = new RepeatStatementNode(en, bn);
		return rsn;
	} else {
		StatementNode *sn = Statement();
		RepeatStatementNode *rsn = new RepeatStatementNode(en, sn);
		return rsn;
	}
}

ProgramNode* ParserClass::ProgramStatement(){
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	BlockNode *bn = BlockStatement();
	ProgramNode *pn = new ProgramNode(bn);
	return pn;
};

BlockNode* ParserClass::BlockStatement(){
	Match(LCURLY_TOKEN);
	StatementGroupNode *sgn = StatementGroup();
	Match(RCURLY_TOKEN);
	BlockNode *bn = new BlockNode(sgn);
	return bn;
}

//NEEDS WORK
ExpressionNode* ParserClass::ExpressionStatement(){
	//ExpressionNode *en = RelationalStatement();
	ExpressionNode *en = OrStatement();
	return en;
}
ExpressionNode* ParserClass::OrStatement(){
	//ExpressionNode *en = RelationalStatement();
	ExpressionNode *current = AndStatement();

	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if(tt == OR_TOKEN){
		Match(tt);
		current = new OrNode(current, AndStatement());
	}
	return current;
}
ExpressionNode* ParserClass::AndStatement(){
	//ExpressionNode *en = RelationalStatement();
	ExpressionNode *current = BitwiseAndStatement();
	
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if(tt == AND_TOKEN){
		Match(tt);
		current = new AndNode(current, RelationalStatement());
	}
	return current;
}

ExpressionNode* ParserClass::BitwiseAndStatement(){
	ExpressionNode *current = RelationalStatement();
	
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if(tt == BITAND_TOKEN){
		Match(tt);
		current = new BitwiseAndNode(current, RelationalStatement());
	}
	return current;
}

ExpressionNode* ParserClass::RelationalStatement()
{
	ExpressionNode *current = PlusMinus();

	// Handle the optional tail:
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if(tt == LESS_TOKEN)
	{
		Match(tt);
		current = new LessNode(current, PlusMinus());
	}
	else if(tt == LESSEQUAL_TOKEN)
	{
		Match(tt);
		current = new LessEqualNode(current, PlusMinus());
	}
	else if(tt == GREATER_TOKEN)
	{
		Match(tt);
		current = new GreaterNode(current, PlusMinus());
	}
	else if(tt == GREATEREQUAL_TOKEN)
	{
		Match(tt);
		current = new GreaterEqualNode(current, PlusMinus());
	}
	else if(tt == EQUAL_TOKEN)
	{
		Match(tt);
		current = new EqualNode(current, PlusMinus());
	}
	else if(tt == NOTEQUAL_TOKEN)
	{
		Match(tt);
		current = new NotEqualNode(current, PlusMinus());
	}
	else
	{
		return current;
	}
	return current;
}

ExpressionNode* ParserClass::PlusMinus()
{
	ExpressionNode* current = TimesDivide();
	while(true)
	{
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if(tt == PLUS_TOKEN)
		{
			Match(tt);
			current = new PlusNode(current, TimesDivide());
		}
		else if(tt == MINUS_TOKEN)
		{
			Match(tt);
			current = new MinusNode(current, TimesDivide());
		}
		else
		{
			return current;
		}
	}
}

ExpressionNode* ParserClass::TimesDivide()
{
	ExpressionNode* current = Factor();
	while(true){
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if(tt == TIMES_TOKEN)
		{
			Match(tt);
			current = new TimesNode(current, Factor());
		}
		else if(tt == DIVIDE_TOKEN)
		{
			Match(tt);
			current = new DivideNode(current, Factor());
		}
		else if(tt == EXPONENT_TOKEN){
			Match(tt);
			current = new ExponentNode(current, Factor());
		}
		else {
			return current;
		}
	}
}

ExpressionNode* ParserClass::Factor(){
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if(tt == IDENTIFIER_TOKEN){
		IdentifierNode *in = Identifier();
		return in;
	}
	if(tt == INTEGER_TOKEN){
		IntegerNode *in = Integer();
		return in;
	}
	else{
		Match(tt);
		ExpressionNode *en = ExpressionStatement();
		Match(RPAREN_TOKEN);
		return en;
	}
}
IntegerNode* ParserClass::Integer(){
	TokenClass tc = Match(INTEGER_TOKEN);
	std::string s = tc.GetLexeme();
	int i = std::atoi(s.c_str());
	IntegerNode *in = new IntegerNode(i);
	return in;
}