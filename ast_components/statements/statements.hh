#ifndef COMPILER_STATEMENTS_HH
#define COMPILER_STATEMENTS_HH

#include <memory>

#include "declarations/variable_declaration.hh"
#include "expressions/expression_base.hh"
#include "invocation.hh"
#include "lvalue.hh"

class TStatement : public INode {};


using TStatementPtr = std::unique_ptr<TStatement>;


class TAssertionStatement : public TStatement {
public:
    explicit TAssertionStatement(TExpressionPtr&& expression) : Expression_(std::move(expression)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    };

    TExpression* Expression() {
        return Expression_.get();
    }

private:
    TExpressionPtr Expression_;
};


class TVariableDeclarationStatement : public TStatement {
public:
    explicit TVariableDeclarationStatement(TVariable&& declaration) : Variable_(std::move(declaration)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    [[nodiscard]] const TVariable& Variable() const {
        return Variable_;
    }

private:
    TVariable Variable_;
};


using TVariableDeclarationStatementPtr = std::unique_ptr<TVariableDeclarationStatement>;


class TStatementList : public TStatement, public std::vector<TStatementPtr> {
public:
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TStatementListPtr = std::unique_ptr<TStatementList>;


class TIfStatement : public TStatement {
public:
    explicit TIfStatement(TExpressionPtr&& condition, TStatementPtr&& statement)
        : Condition_(std::move(condition)), Statement_(std::move(statement)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    TExpression* Condition() {
        return Condition_.get();
    }

    TStatement* Statement() {
        return Statement_.get();
    }

private:
    TExpressionPtr Condition_;
    TStatementPtr Statement_;
};


using TIfStatementPtr = std::unique_ptr<TIfStatement>;


class TIfElseStatement : public TIfStatement {
public:
    explicit TIfElseStatement(TExpressionPtr&& condition, TStatementPtr&& statement, TStatementPtr&& elseStatement)
        : TIfStatement(std::move(condition), std::move(statement)), ElseStatement_(std::move(elseStatement)) {}

    TStatement* ElseStatement() {
        return ElseStatement_.get();
    }

private:
    TStatementPtr ElseStatement_;
};


using TIfElseStatementPtr = std::unique_ptr<TIfElseStatement>;


class TWhileStatement : public TStatement {
public:
    explicit TWhileStatement(TExpressionPtr&& condition, TStatementPtr&& statement)
        : Condition_(std::move(condition)), Statement_(std::move(statement)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    TExpression* Condition() {
        return Condition_.get();
    }

    TStatement* Statement() {
        return Statement_.get();
    }

private:
    TExpressionPtr Condition_;
    TStatementPtr Statement_;
};


using TWhileStatementPtr = std::unique_ptr<TWhileStatement>;


class TPrintlnStatement : public TStatement {
public:
    explicit TPrintlnStatement(TExpressionPtr&& expression) : Expression_(std::move(expression)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    TExpression* Expression() {
        return Expression_.get();
    }

private:
    TExpressionPtr Expression_;
};


using TPrintlnStatementPtr = std::unique_ptr<TPrintlnStatement>;


class TAssignmentStatement : public TStatement {
public:
    explicit TAssignmentStatement(TLvaluePtr&& lvalue, TExpressionPtr&& expression)
        : Lvalue_(std::move(lvalue)), Expression_(std::move(expression)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    TLvalue* Lvalue() {
        return Lvalue_.get();
    }

    TExpression* Expression() {
        return Expression_.get();
    }

private:
    TLvaluePtr Lvalue_;
    TExpressionPtr Expression_;
};


using TAssignmentStatementPtr = std::unique_ptr<TAssignmentStatement>;


class TReturnStatement : public TStatement {
public:
    explicit TReturnStatement(TExpressionPtr&& expression) : Expression_(std::move(expression)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    TExpression* Expression() {
        return Expression_.get();
    }

private:
    TExpressionPtr Expression_;
};


using TReturnStatementPtr = std::unique_ptr<TReturnStatement>;


class TMethodInvocationStatement : public TStatement {
public:
    explicit TMethodInvocationStatement(TMethodInvocationPtr&& method) : Method_(std::move(method)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    TMethodInvocation* Method() {
        return Method_.get();
    }

private:
    TMethodInvocationPtr Method_;
};


using TMethodInvocationStatementPtr = std::unique_ptr<TMethodInvocationStatement>;


#endif//COMPILER_STATEMENTS_HH
