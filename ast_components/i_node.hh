#ifndef COMPILER_I_ELEM_HH
#define COMPILER_I_ELEM_HH

#include "i_visitor.hh"

class INode {
public:
    INode() = default;

    INode(INode&& other) = default;
    INode& operator=(INode&& other) = default;

    INode(const INode& other) = delete;
    INode& operator=(const INode& other) = delete;

    virtual void Accept(IVisitor* visitor) = 0;
    virtual ~INode()                       = default;
};

#endif//COMPILER_I_ELEM_HH
