#ifndef COMPILER_EXPRESSION_HH
#define COMPILER_EXPRESSION_HH

#include <memory>
#include <vector>

#include "expression_base.hh"
#include "invocation.hh"

class TBinaryExpression : public TExpression {
public:
    explicit TBinaryExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs) : Lhs(std::move(lhs)), Rhs(std::move(rhs)) {}

private:
    TExpressionPtr Lhs, Rhs;
};


using TBinaryExpressionPtr = std::unique_ptr<TBinaryExpression>;


class TAndExpression : public TBinaryExpression {
public:
    explicit TAndExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
};


using TAndExpressionPtr = std::unique_ptr<TAndExpression>;


class TOrExpression : public TBinaryExpression {
public:
    explicit TOrExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
};


using TOrExpressionPtr = std::unique_ptr<TOrExpression>;


class TSumExpression : public TBinaryExpression {
public:
    explicit TSumExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
};


using TSumExpressionPtr = std::unique_ptr<TSumExpression>;


class TSubExpression : public TBinaryExpression {
public:
    explicit TSubExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
};


using TSubExpressionPtr = std::unique_ptr<TSumExpression>;


class TMulExpression : public TBinaryExpression {
public:
    explicit TMulExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
};


using TMulExpressionPtr = std::unique_ptr<TMulExpression>;


class TDivExpression : public TBinaryExpression {
public:
    explicit TDivExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
};


using TDivExpressionPtr = std::unique_ptr<TDivExpression>;


class TModExpression : public TBinaryExpression {
public:
    explicit TModExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
};


using TModExpressionPtr = std::unique_ptr<TModExpression>;


class TEqExpression : public TBinaryExpression {
public:
    explicit TEqExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
};


using TEqExpressionPtr = std::unique_ptr<TEqExpression>;


class TLeExpression : public TBinaryExpression {
public:
    explicit TLeExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
};


using TLeExpressionPtr = std::unique_ptr<TLeExpression>;


class TGeExpression : public TBinaryExpression {
public:
    explicit TGeExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
};


using TGeExpressionPtr = std::unique_ptr<TGeExpression>;


class TLeqExpression : public TBinaryExpression {
public:
    explicit TLeqExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
};


using TLeqExpressionPtr = std::unique_ptr<TLeqExpression>;


class TGeqExpression : public TBinaryExpression {
public:
    explicit TGeqExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
};


using TGeqExpressionPtr = std::unique_ptr<TGeqExpression>;


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

#endif//COMPILER_EXPRESSION_HH
