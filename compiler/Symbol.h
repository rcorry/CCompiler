#include <string>
#include <vector>
#include <iostream>


class SymbolTableClass {
    struct Variable {
        std::string mLabel;
        int mValue;
    };

public:
    SymbolTableClass();
    bool Exists(const std::string &s);
    void AddEntry(const std::string &s);
    int GetValue(const std::string &s);
    void SetValue(const std::string &s, int v);
    int GetIndex(const std::string &s);
    int GetCount();

private:
    std::vector<Variable> mVariables;

};