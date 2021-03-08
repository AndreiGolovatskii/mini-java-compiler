#ifndef COMPILER_STATEMENTS_HH
#define COMPILER_STATEMENTS_HH

#include <memory>

#include "declarations/variable_declaration.hh"
#include "expressions/expression_base.hh"
#include "invocation.hh"
#include "lvalue.hh"

class TStatement {
public:
    virtual ~TStatement() = default;
};


using TStatementPtr = std::unique_ptr<TStatement>;


class TAssertionStatement : public TStatement {
public:
    explicit TAssertionStatement(TExpressionPtr&& expression) : Expression_(std::move(expression)){};

private:
    TExpressionPtr Expression_;
};


class TVariableDeclarationStatement : public TStatement {
public:
    explicit TVariableDeclarationStatement(TVariableDeclarationPtr&& declaration)
        : Declaration_(std::move(declaration)) {}

private:
    TVariableDeclarationPtr Declaration_;
};


using TVariableDeclarationStatementPtr = std::unique_ptr<TVariableDeclarationStatement>;


class TStatementList : public TStatement, public std::vector<TStatementPtr> {};


using TStatementListPtr = std::unique_ptr<TStatementList>;


class TIfStatement : public TStatement {
public:
    explicit TIfStatement(TExpressionPtr&& condition, TStatementPtr&& statement)
        : Condition_(std::move(condition)), Statement_(std::move(statement)) {}

private:
    TExpressionPtr Condition_;
    TStatementPtr Statement_;
};


using TIfStatementPtr = std::unique_ptr<TIfStatement>;


class TIfElseStatement : public TIfStatement {
public:
    explicit TIfElseStatement(TExpressionPtr&& condition, TStatementPtr&& statement, TStatementPtr&& elseStatement)
        : TIfStatement(std::move(condition), std::move(elseStatement)), ElseStatement_(std::move(elseStatement)) {}

private:
    TStatementPtr ElseStatement_;
};


using TIfElseStatementPtr = std::unique_ptr<TIfElseStatement>;


class TWhileStatement : public TStatement {
public:
    explicit TWhileStatement(TExpressionPtr&& condition, TStatementPtr&& statement)
        : Condition_(std::move(condition)), Statement_(std::move(statement)) {}

private:
    TExpressionPtr Condition_;
    TStatementPtr Statement_;
};


using TWhileStatementPtr = std::unique_ptr<TWhileStatement>;


class TPrintlnStatement : public TStatement {
public:
    explicit TPrintlnStatement(TExpressionPtr&& expression) : Expression_(std::move(expression)) {}

private:
    TExpressionPtr Expression_;
};


using TPrintlnStatementPtr = std::unique_ptr<TPrintlnStatement>;


class TAssignmentStatement : public TStatement {
public:
    explicit TAssignmentStatement(TLvaluePtr&& lvalue, TExpressionPtr&& expression)
        : Lvalue_(std::move(lvalue)), Expression_(std::move(expression)) {}

private:
    TLvaluePtr Lvalue_;
    TExpressionPtr Expression_;
};


using TAssignmentStatementPtr = std::unique_ptr<TAssignmentStatement>;


class TReturnStatement : public TStatement {
public:
    explicit TReturnStatement(TExpressionPtr&& expression) : Expression_(std::move(expression)) {}

private:
    TExpressionPtr Expression_;
};


using TReturnStatementPtr = std::unique_ptr<TReturnStatement>;


class TMethodInvocationStatement : public TStatement {
public:
    explicit TMethodInvocationStatement(TMethodInvocationPtr&& method) : Method_(std::move(method)) {}

private:
    TMethodInvocationPtr Method_;
};


using TMethodInvocationStatementPtr = std::unique_ptr<TMethodInvocationStatement>;


#endif//COMPILER_STATEMENTS_HH
