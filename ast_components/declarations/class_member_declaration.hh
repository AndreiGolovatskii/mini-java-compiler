#ifndef COMPILER_CLASS_MEMBER_DECLARATION_HH
#define COMPILER_CLASS_MEMBER_DECLARATION_HH

#include <memory>
#include <vector>

#include "types/type.hh"


class TClassMemberDeclaration : public INode {};


using TClassMemberDeclarationPtr = std::unique_ptr<TClassMemberDeclaration>;


class TClassMemberDeclarationList : public TClassMemberDeclaration, public std::vector<TClassMemberDeclarationPtr> {
public:
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};


using TDeclarationListPtr = std::unique_ptr<TClassMemberDeclarationList>;


#endif//COMPILER_CLASS_MEMBER_DECLARATION_HH
