#ifndef COMPILER_BINARY_EXPRESSIONS_HH
#define COMPILER_BINARY_EXPRESSIONS_HH

#include "expression_base.hh"


class TBinaryExpression : public TExpression {
public:
    explicit TBinaryExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : Lhs_(std::move(lhs)), Rhs_(std::move(rhs)) {}

    TExpression* Lhs() {
        return Lhs_.get();
    }

    TExpression* Rhs() {
        return Rhs_.get();
    }

private:
    TExpressionPtr Lhs_, Rhs_;
};


using TBinaryExpressionPtr = std::unique_ptr<TBinaryExpression>;


class TAndExpression : public TBinaryExpression {
public:
    explicit TAndExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TAndExpressionPtr = std::unique_ptr<TAndExpression>;


class TOrExpression : public TBinaryExpression {
public:
    explicit TOrExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TOrExpressionPtr = std::unique_ptr<TOrExpression>;


class TSumExpression : public TBinaryExpression {
public:
    explicit TSumExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TSumExpressionPtr = std::unique_ptr<TSumExpression>;


class TSubExpression : public TBinaryExpression {
public:
    explicit TSubExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TSubExpressionPtr = std::unique_ptr<TSumExpression>;


class TMulExpression : public TBinaryExpression {
public:
    explicit TMulExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TMulExpressionPtr = std::unique_ptr<TMulExpression>;


class TDivExpression : public TBinaryExpression {
public:
    explicit TDivExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TDivExpressionPtr = std::unique_ptr<TDivExpression>;


class TModExpression : public TBinaryExpression {
public:
    explicit TModExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TModExpressionPtr = std::unique_ptr<TModExpression>;


class TEqExpression : public TBinaryExpression {
public:
    explicit TEqExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TEqExpressionPtr = std::unique_ptr<TEqExpression>;


class TLeExpression : public TBinaryExpression {
public:
    explicit TLeExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TLeExpressionPtr = std::unique_ptr<TLeExpression>;


class TGeExpression : public TBinaryExpression {
public:
    explicit TGeExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TGeExpressionPtr = std::unique_ptr<TGeExpression>;


class TLeqExpression : public TBinaryExpression {
public:
    explicit TLeqExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TLeqExpressionPtr = std::unique_ptr<TLeqExpression>;


class TGeqExpression : public TBinaryExpression {
public:
    explicit TGeqExpression(TExpressionPtr&& lhs, TExpressionPtr&& rhs)
        : TBinaryExpression(std::move(lhs), std::move(rhs)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};

using TGeqExpressionPtr = std::unique_ptr<TGeqExpression>;

#endif//COMPILER_BINARY_EXPRESSIONS_HH
