#ifndef COMPILER_SYMBOL_HH
#define COMPILER_SYMBOL_HH

#include <string>

class TSymbol {
public:
    explicit TSymbol(const std::string& name) : Name_(name) {}

private:
    std::string Name_;
};


#endif//COMPILER_SYMBOL_HH
