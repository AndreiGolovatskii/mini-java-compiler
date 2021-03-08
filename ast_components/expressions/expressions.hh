#ifndef COMPILER_EXPRESSIONS_HH
#define COMPILER_EXPRESSIONS_HH

#include <memory>
#include <vector>

#include "expressions/binary_expressions.hh"
#include "expressions/expression_base.hh"
#include "invocation.hh"


class TNotExpression : public TExpression {
public:
    explicit TNotExpression(TExpressionPtr&& expression) : Expression_(std::move(expression)) {}

private:
    TExpressionPtr Expression_;
};


using TNotExpressionPtr = std::unique_ptr<TNotExpression>;


class TIndexExpression : public TExpression {
public:
    explicit TIndexExpression(TExpressionPtr&& expression, TExpressionPtr&& index)
        : Expression_(std::move(expression)), Index_(std::move(index)) {}

private:
    TExpressionPtr Expression_;
    TExpressionPtr Index_;
};


using TIndexExpressionPtr = std::unique_ptr<TIndexExpression>;


class TLengthExpression : public TExpression {
public:
    explicit TLengthExpression(TExpressionPtr&& expression) : Expression_(std::move(expression)) {}

private:
    TExpressionPtr Expression_;
};


using TLengthExpressionPtr = std::unique_ptr<TLengthExpression>;


class TNewExpression : public TExpression {
public:
    explicit TNewExpression(TTypePtr&& type) : Type_(std::move(type)) {}

private:
    TTypePtr Type_;
};


using TNewExpressionPtr = std::unique_ptr<TNewExpression>;


class TNewArrayExpression : public TExpression {
public:
    explicit TNewArrayExpression(TTypePtr&& type, TExpressionPtr&& size)
        : Type_(std::move(type)), Size_(std::move(size)) {}

private:
    TTypePtr Type_;
    TExpressionPtr Size_;
};


using TNewArrayExpressionPtr = std::unique_ptr<TNewArrayExpression>;


class TIdentifierExpression : public TExpression {
public:
    explicit TIdentifierExpression(std::string&& identifier) : Identifier_(std::move(identifier)) {}

private:
    const std::string Identifier_;
};


using TIdentifierExpressionPtr = std::unique_ptr<TIdentifierExpression>;


class TIntExpression : public TExpression {
public:
    explicit TIntExpression(int value) : Value_(value) {}

private:
    const int Value_;
};


using TIntExpressionPtr = std::unique_ptr<TIntExpression>;


class TThisExpression : public TExpression {};


using TThisExpressionPtr = std::unique_ptr<TThisExpression>;


class TBooleanExpression : public TExpression {
public:
    explicit TBooleanExpression(bool value) : Value_(value) {}

private:
    const bool Value_;
};


using TBooleanExpressionPtr = std::unique_ptr<TBooleanExpression>;


class TMethodInvocationExpression : public TExpression {
public:
    explicit TMethodInvocationExpression(TMethodInvocationPtr&& method) : Method_(std::move(method)) {}

private:
    TMethodInvocationPtr Method_;
};

using TMethodInvocationExpressionPtr = std::unique_ptr<TMethodInvocationExpression>;


class TFieldInvocationExpression : public TExpression {
public:
    explicit TFieldInvocationExpression(TFieldInvocationPtr&& method) : Method_(std::move(method)) {}

private:
    TFieldInvocationPtr Method_;
};

using TMethodInvocationExpressionPtr = std::unique_ptr<TMethodInvocationExpression>;

#endif//COMPILER_EXPRESSIONS_HH
