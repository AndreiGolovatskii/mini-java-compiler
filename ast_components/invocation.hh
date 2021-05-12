#ifndef COMPILER_INVOCATION_HH
#define COMPILER_INVOCATION_HH

#include <memory>
#include <string>
#include <utility>

#include "expressions/expression_base.hh"
#include "i_node.hh"

class TMethodInvocation : public INode {
public:
    explicit TMethodInvocation(TExpressionPtr&& expression, std::string&& method, TExpressionListPtr&& arguments)
        : Expression_(std::move(expression)), Method_(std::move(method)), Arguments_(std::move(arguments)) {}

    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    [[nodiscard]] TExpression* Expression() const {
        return Expression_.get();
    }

    [[nodiscard]] const std::string& Method() const {
        return Method_;
    }

    [[nodiscard]] TExpressionList* Arguments() const {
        return Arguments_.get();
    }

private:
    TExpressionPtr Expression_;
    std::string Method_;
    TExpressionListPtr Arguments_;
};


using TMethodInvocationPtr = std::unique_ptr<TMethodInvocation>;

class TFieldInvocation : public INode {
public:
    explicit TFieldInvocation(TExpressionPtr&& expression, std::string identifier)
        : Expression_(std::move(expression)), Identifier_(std::move(identifier)) {}

    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    [[nodiscard]] TExpression* Expression() const {
        return Expression_.get();
    }

    [[nodiscard]] const std::string& Identifier() const {
        return Identifier_;
    }

private:
    TExpressionPtr Expression_;
    std::string Identifier_;
};


using TFieldInvocationPtr = std::unique_ptr<TFieldInvocation>;


/*
class TFieldInvocationIndexed : public TFieldInvocation {
public:
    explicit TFieldInvocationIndexed(std::string&& identifier, TExpressionPtr&& index)
        : TFieldInvocation(std::move(identifier)), Index_(std::move(index)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    [[nodiscard]] TExpression* Index() const {
        return Index_.get();
    }

private:
    TExpressionPtr Index_;
};


using TFieldInvocationIndexedPtr = std::unique_ptr<TFieldInvocationIndexed>;
 */

#endif//COMPILER_INVOCATION_HH
