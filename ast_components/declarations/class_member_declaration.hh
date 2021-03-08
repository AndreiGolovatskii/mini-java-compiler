#ifndef COMPILER_CLASS_MEMBER_DECLARATION_HH
#define COMPILER_CLASS_MEMBER_DECLARATION_HH

#include <memory>
#include <vector>

#include "types/type.hh"


class TClassMemberDeclaration {
public:
    virtual ~TClassMemberDeclaration() = default;
};


using TClassMemberDeclarationPtr = std::unique_ptr<TClassMemberDeclaration>;


class TClassMemberDeclarationList : public TClassMemberDeclaration, public std::vector<TClassMemberDeclarationPtr> {};


using TDeclarationListPtr = std::unique_ptr<TClassMemberDeclarationList>;


#endif//COMPILER_CLASS_MEMBER_DECLARATION_HH
