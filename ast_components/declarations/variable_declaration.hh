#ifndef COMPILER_VARIABLE_DECLARATION_HH
#define COMPILER_VARIABLE_DECLARATION_HH

#include <memory>
#include <string>

#include "declarations/class_member_declaration.hh"
#include "declarations/variable.hh"


class TMemberVariableDeclaration : public TClassMemberDeclaration {
public:
    explicit TMemberVariableDeclaration(TVariable&& variable) : Variable_(std::move(variable)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    [[nodiscard]] const TVariable& Variable() const {
        return Variable_;
    }

private:
    TVariable Variable_;
};

using TMemberVariableDeclarationPtr = std::unique_ptr<TMemberVariableDeclaration>;

#endif//COMPILER_VARIABLE_DECLARATION_HH
