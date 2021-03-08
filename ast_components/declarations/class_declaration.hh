#ifndef COMPILER_CLASS_DECLARATION_HH
#define COMPILER_CLASS_DECLARATION_HH

#include <string>
#include <vector>

#include "method_declaration.hh"


class TClassDeclaration {
public:
    explicit TClassDeclaration(std::string&& className, std::string&& extends = "object")
        : ClassName_(std::move(className)), Extends_(std::move(extends)) {}

    void AddMethod(TMethodDeclarationPtr&& method) {
        Members_.emplace_back(std::move(method));
    }

    void AddMethods(TDeclarationListPtr&& declarations) {
        std::move(declarations->begin(), declarations->end(), std::back_inserter(Members_));
    }

    virtual ~TClassDeclaration() = default;

private:
    std::string ClassName_;
    std::string Extends_;
    TClassMemberDeclarationList Members_;
};


using TClassDeclarationPtr = std::unique_ptr<TClassDeclaration>;


class TClassDeclarationList : public std::vector<TClassDeclarationPtr> {};


#endif//COMPILER_CLASS_DECLARATION_HH
