#ifndef COMPILER_METHOD_DECLARATION_HH
#define COMPILER_METHOD_DECLARATION_HH

#include <string>

#include "class_member_declaration.hh"
#include "statements/statements.hh"


class TMethodSignature {
public:
    explicit TMethodSignature(std::string&& name, TVariableList&& arguments)
        : Name_(std::move(name)), Arguments_(std::move(arguments)) {}

private:
    std::string Name_;
    TVariableList Arguments_;
};


class TMethodDeclaration : public TClassMemberDeclaration {
public:
    explicit TMethodDeclaration(TTypePtr&& returnType, TMethodSignature&& signature, TStatementListPtr&& statements)
        : ReturnType_(std::move(returnType)), Signature_(std::move(signature)), Statements_(std::move(statements)) {}

    void MakeStatic() {
        Static_ = true;
    }

private:
    bool Static_ = false;
    TTypePtr ReturnType_;
    TMethodSignature Signature_;
    TStatementListPtr Statements_;
};

using TMethodDeclarationPtr = std::unique_ptr<TMethodDeclaration>;

#endif//COMPILER_METHOD_DECLARATION_HH
