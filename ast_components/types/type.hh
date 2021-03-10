#ifndef COMPILER_TYPE_HH
#define COMPILER_TYPE_HH

#include <memory>

class TType : public INode {
public:
    void MakeArray() {
        IsArray_ = true;
    }

    [[nodiscard]] bool IsArray() const {
        return IsArray_;
    }

private:
    bool IsArray_ = false;
};


using TTypePtr = std::unique_ptr<TType>;


class TVoidType : public TType {
public:
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TVoidTypePtr = std::unique_ptr<TVoidType>;


class TIntType : public TType {
public:
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TIntTypePtr = std::unique_ptr<TIntType>;


class TBooleanType : public TType {
public:
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TBooleanTypePtr = std::unique_ptr<TBooleanType>;


class TIdentifierType : public TType {
public:
    explicit TIdentifierType(std::string&& identifier) : Identifier_(std::move(identifier)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    [[nodiscard]] const std::string& Identifier() const {
        return Identifier_;
    }

private:
    std::string Identifier_;
};


using TIdentifierTypePtr = std::unique_ptr<TIdentifierType>;

#endif//COMPILER_TYPE_HH
