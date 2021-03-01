#ifndef COMPILER_DECLARATION_HH
#define COMPILER_DECLARATION_HH

#include <memory>
#include <vector>

#include "type.hh"


class TDeclaration {
public:
    virtual ~TDeclaration() = default;
};


using TDeclarationPtr = std::unique_ptr<TDeclaration>;


class TDeclarationList : public TDeclaration, public std::vector<TDeclarationPtr> {};


using TDeclarationListPtr = std::unique_ptr<TDeclarationList>;


class TVariable {
public:
    explicit TVariable(TTypePtr&& type, std::string&& name) : Type_(std::move(type)), Name_(std::move(name)) {}

private:
    TTypePtr Type_;
    std::string Name_;
};

using TVariableList = std::vector<TVariable>;

#endif//COMPILER_DECLARATION_HH
