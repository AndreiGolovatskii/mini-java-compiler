#ifndef COMPILER_TYPE_HH
#define COMPILER_TYPE_HH

#include <memory>
#include <string>

#include "i_node.hh"

class TTypeNode : public INode {
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


using TTypeNodePtr = std::unique_ptr<TTypeNode>;


class TVoidTypeNode : public TTypeNode {
public:
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TVoidTypeNodePtr = std::unique_ptr<TVoidTypeNode>;


class TIntTypeNode : public TTypeNode {
public:
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TIntTypeNodePtr = std::unique_ptr<TIntTypeNode>;


class TBooleanTypeNode : public TTypeNode {
public:
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TBooleanTypeNodePtr = std::unique_ptr<TBooleanTypeNode>;


class TIdentifierTypeNode : public TTypeNode {
public:
    explicit TIdentifierTypeNode(std::string&& identifier) : Identifier_(std::move(identifier)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    [[nodiscard]] const std::string& Identifier() const {
        return Identifier_;
    }

private:
    std::string Identifier_;
};


using TIdentifierTypeNodePtr = std::unique_ptr<TIdentifierTypeNode>;

#endif//COMPILER_TYPE_HH
