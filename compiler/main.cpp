#include "scanner.h"
#include "Node.h"
#include "Parser.h"

void Interpret(std::string filename){
    ScannerClass scanner(filename);
    SymbolTableClass st;
    ParserClass parser(&scanner, &st);
    StartNode *root = parser.Start();
    root->Interpret();

}

int main(){
    std::string filename = "sample.txt";
    Interpret(filename);
    
    return 1;
}
