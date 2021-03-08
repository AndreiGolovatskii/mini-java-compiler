#ifndef COMPILER_VARIABLE_HH
#define COMPILER_VARIABLE_HH

#include <string>

#include "types/type.hh"

class TVariable {
public:
    explicit TVariable(TTypePtr&& type, std::string&& name) : Type_(std::move(type)), Name_(std::move(name)) {}

private:
    TTypePtr Type_;
    std::string Name_;
};

using TVariableList = std::vector<TVariable>;

#endif//COMPILER_VARIABLE_HH
