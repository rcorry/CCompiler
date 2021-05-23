#include "Symbol.h"

SymbolTableClass::SymbolTableClass(){

}

bool SymbolTableClass::Exists(const std::string &s){
    for(int i=0; i<(int)mVariables.size(); i++){
        if(mVariables[i].mLabel == s){
            return true;
        }
    }
    return false;
}

void SymbolTableClass::AddEntry(const std::string &s){
    if(!Exists(s)){
        Variable v;
        v.mLabel = s;
        v.mValue = 0;
        mVariables.push_back(v);
    } else{
        std::cout << "Cannot Insert, Variable " << s << " Already Exists" << std::endl;
        exit(0);
    }
    
}

int SymbolTableClass::GetValue(const std::string &s){
    int index = GetIndex(s);
    if(index != -1){
        return mVariables[index].mValue;
    } else {
        std::cout << "Cannot Retieve Variable " << s << " Does Not Exist" << std::endl;
        exit(0);
    }
}

void SymbolTableClass::SetValue(const std::string &s, int v){
    int index = GetIndex(s);
    if(index != -1){
        mVariables[index].mValue = v;
    } else {
        std::cout << "Cannot Set Value " << v << " For Variable " << s << " That Does Not Exist"<< std::endl;
    }

}

int SymbolTableClass::GetIndex(const std::string & s){
    for(int i=0; i<(int)mVariables.size(); i++){
        if (mVariables[i].mLabel == s){
            return i;
        }
    }
    return -1;
}

int SymbolTableClass::GetCount(){
    return mVariables.size();
}

