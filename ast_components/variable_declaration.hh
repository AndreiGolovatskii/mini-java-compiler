#ifndef COMPILER_VARIABLE_DECLARATION_HH
#define COMPILER_VARIABLE_DECLARATION_HH

#include <memory>
#include <string>

#include "declaration.hh"


class TVariableDeclaration : public TDeclaration {
public:
    explicit TVariableDeclaration(TVariable&& variable) : Variable_(std::move(variable)) {}

private:
    TVariable Variable_;
};

using TVariableDeclarationPtr = std::unique_ptr<TVariableDeclaration>;

#endif//COMPILER_VARIABLE_DECLARATION_HH
