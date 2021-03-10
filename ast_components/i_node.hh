#ifndef COMPILER_I_ELEM_HH
#define COMPILER_I_ELEM_HH

#include "i_visitor.hh"

class INode {
public:
    virtual void Accept(IVisitor* visitor) = 0;
    virtual ~INode()                       = default;
};

#endif//COMPILER_I_ELEM_HH
