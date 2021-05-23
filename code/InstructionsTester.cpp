#include <iostream>
#include "Instructions.h"

int main(){
    InstructionsClass code;
    //code.PushValue(100);
    //code.PopAndWrite();
    code.Finish();
    code.Execute();
    std::cout << "Success" << std::endl;

    return 1;
}