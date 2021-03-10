#ifndef COMPILER_LVALUE_HH
#define COMPILER_LVALUE_HH

#include <memory>

class TLvalue : public INode {};

using TLvaluePtr = std::unique_ptr<TLvalue>;


class TLvalueIdentifier : public TLvalue {
public:
    explicit TLvalueIdentifier(std::string&& identifier) : Identifier_(identifier) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    const std::string& Identifier() const {
        return Identifier_;
    }

private:
    std::string Identifier_;
};


using TLvalueIdentifierPtr = std::unique_ptr<TLvalueIdentifier>;


class TLvalueIdentifierIndexed : public TLvalueIdentifier {
public:
    explicit TLvalueIdentifierIndexed(std::string&& identifier, TExpressionPtr index)
        : TLvalueIdentifier(std::move(identifier)), Index_(std::move(index)) {}

    TExpression* Index() const {
        return Index_.get();
    }

private:
    TExpressionPtr Index_;
};


using TLvalueIdentifierIndexedPtr = std::unique_ptr<TLvalueIdentifierIndexed>;


class TLvalueFieldInvocation : public TLvalue {
public:
    explicit TLvalueFieldInvocation(TFieldInvocationPtr&& field) : Invocation_(std::move(field)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    TFieldInvocation* Invocation() const {
        return Invocation_.get();
    }

private:
    TFieldInvocationPtr Invocation_;
};


using TLvalueFieldInvocationPtr = std::unique_ptr<TLvalueFieldInvocation>;

#endif//COMPILER_LVALUE_HH
