#ifndef COMPILER_LVALUE_HH
#define COMPILER_LVALUE_HH

#include <memory>

class TLvalue {
public:
    virtual ~TLvalue() = default;
};

using TLvaluePtr = std::unique_ptr<TLvalue>;


class TLvalueIdentifier : public TLvalue {
public:
    explicit TLvalueIdentifier(std::string&& identifier) : Identifier_(identifier) {}

private:
    std::string Identifier_;
};


using TLvalueIdentifierPtr = std::unique_ptr<TLvalueIdentifier>;


class TLvalueIdentifierIndexed : public TLvalueIdentifier {
public:
    explicit TLvalueIdentifierIndexed(std::string&& identifier, TExpressionPtr index)
        : TLvalueIdentifier(std::move(identifier)), Index_(std::move(index)) {}

private:
    TExpressionPtr Index_;
};


using TLvalueIdentifierIndexedPtr = std::unique_ptr<TLvalueIdentifierIndexed>;


class TLvalueFieldInvocation : public TLvalue {
public:
    explicit TLvalueFieldInvocation(TFieldInvocationPtr&& field) : Field_(std::move(field)) {}

private:
    TFieldInvocationPtr Field_;
};


using TLvalueFieldInvocationPtr = std::unique_ptr<TLvalueFieldInvocation>;

#endif//COMPILER_LVALUE_HH
