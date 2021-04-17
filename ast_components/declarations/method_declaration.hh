#ifndef COMPILER_METHOD_DECLARATION_HH
#define COMPILER_METHOD_DECLARATION_HH

#include <string>

#include "class_member_declaration.hh"
#include "declarations/variable.hh"
#include "statements/statements.hh"


class TMethodSignature {
public:
    explicit TMethodSignature(std::string&& name, TVariableList&& arguments)
        : Name_(std::move(name)), Arguments_(std::move(arguments)) {}

    [[nodiscard]] const std::string& Name() const {
        return Name_;
    }

    [[nodiscard]] const TVariableList& Arguments() const {
        return Arguments_;
    }

private:
    const std::string Name_;
    TVariableList Arguments_;
};


class TMemberMethodDeclaration : public TClassMemberDeclaration {
public:
    explicit TMemberMethodDeclaration(TTypeNodePtr&& returnType, TMethodSignature&& signature,
                                      TStatementListPtr&& statements)
        : ReturnType_(std::move(returnType)), Signature_(std::move(signature)), Statements_(std::move(statements)) {}

    void MakeStatic() {
        Static_ = true;
    }
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    [[nodiscard]] const TMethodSignature& Signature() const {
        return Signature_;
    }

    [[nodiscard]] bool IsStatic() const {
        return Static_;
    }

    [[nodiscard]] TTypeNode* ReturnType() const {
        return ReturnType_.get();
    }

    [[nodiscard]] TStatementList* Statements() const {
        return Statements_.get();
    }

private:
    bool Static_ = false;
    const TTypeNodePtr ReturnType_;
    const TMethodSignature Signature_;
    const TStatementListPtr Statements_;
};

using TMethodDeclarationPtr = std::unique_ptr<TMemberMethodDeclaration>;

#endif//COMPILER_METHOD_DECLARATION_HH
