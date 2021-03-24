#pragma once

#include "ast_components.hh"
#include "i_visitor.hh"

template<class ReturnType>
class TTemplateVisitor : public IVisitor {
public:
    ReturnType Accept(INode* node) {
        node->Accept(this);
        return std::move(ReturnValue_);
    }
    void Visit(struct TAndExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TAssertionStatement* statement) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TAssignmentStatement* statement) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TBooleanExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TClassDeclaration* declaration) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TClassMemberDeclarationList* list) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TDivExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TEqExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TExpressionList* list) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TFieldInvocation* invocation) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TFieldInvocationExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TFieldInvocationIndexed* indexed) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TGeExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TGeqExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TIdentifierExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TIfElseStatement* statement) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TIfStatement* statement) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TIndexExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TIntExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TLeExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TLengthExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TLeqExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TMemberMethodDeclaration* declaration) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TMemberVariableDeclaration* declaration) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TMethodInvocation* invocation) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TMethodInvocationExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TMethodInvocationStatement* statement) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TModExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TMulExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TNewArrayExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TNewExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TNotExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TOrExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TPrintlnStatement* statement) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TProgram* program) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TReturnStatement* statement) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TStatementList* list) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TSubExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TSumExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TThisExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TVariableDeclarationStatement* statement) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TWhileStatement* statement) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TClassDeclarationList* list) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TIntTypeNode* type) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TBooleanTypeNode* type) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TVoidTypeNode* type) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TIdentifierTypeNode* type) override {
        throw std::runtime_error{"unimplemented"};
    }
    void Visit(struct TUnaryMinusExpression* expression) override {
        throw std::runtime_error{"unimplemented"};
    }

    void Return(ReturnType value) {
        ReturnValue_ = std::move(value);
    }

private:
    ReturnType ReturnValue_;
};