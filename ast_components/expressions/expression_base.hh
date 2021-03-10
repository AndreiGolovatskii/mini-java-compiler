#ifndef COMPILER_EXPRESSION_BASE_HH
#define COMPILER_EXPRESSION_BASE_HH

#include "i_node.hh"
#include <memory>
#include <vector>

class TExpression : public INode {};


using TExpressionPtr = std::unique_ptr<TExpression>;


class TExpressionList : public TExpression, public std::vector<TExpressionPtr> {
public:
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TExpressionListPtr = std::unique_ptr<TExpressionList>;


#endif//COMPILER_EXPRESSION_BASE_HH
