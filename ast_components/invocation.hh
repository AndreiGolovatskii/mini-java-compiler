#ifndef COMPILER_INVOCATION_HH
#define COMPILER_INVOCATION_HH

#include <memory>
#include <string>

#include "expression_base.hh"

class TMethodInvocation {
public:
    explicit TMethodInvocation(TExpressionPtr&& expression, std::string&& method, TExpressionListPtr&& arguments)
        : Expression_(std::move(expression)), Method_(std::move(method)), Arguments_(std::move(arguments)) {}

    virtual ~TMethodInvocation() = default;

private:
    TExpressionPtr Expression_;
    std::string Method_;
    TExpressionListPtr Arguments_;
};


using TMethodInvocationPtr = std::unique_ptr<TMethodInvocation>;

class TFieldInvocation {
public:
    explicit TFieldInvocation(std::string&& identifier) : Identifier_(identifier) {}

    virtual ~TFieldInvocation() = default;

private:
    std::string Identifier_;
};


using TFieldInvocationPtr = std::unique_ptr<TFieldInvocation>;


class TFieldInvocationIndexed : public TFieldInvocation {
public:
    explicit TFieldInvocationIndexed(std::string&& identifier, TExpressionPtr&& index)
        : TFieldInvocation(std::move(identifier)), Index_(std::move(index)) {}

private:
    TExpressionPtr Index_;
};


using TFieldInvocationIndexedPtr = std::unique_ptr<TFieldInvocationIndexed>;

#endif//COMPILER_INVOCATION_HH
