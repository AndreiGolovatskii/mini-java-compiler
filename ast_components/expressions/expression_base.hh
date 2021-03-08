#ifndef COMPILER_EXPRESSION_BASE_HH
#define COMPILER_EXPRESSION_BASE_HH

#include <memory>
#include <vector>

class TExpression {
public:
    virtual ~TExpression() = default;
};


using TExpressionPtr = std::unique_ptr<TExpression>;


class TExpressionList : public TExpression, public std::vector<TExpressionPtr> {};


using TExpressionListPtr = std::unique_ptr<TExpressionList>;


#endif//COMPILER_EXPRESSION_BASE_HH
