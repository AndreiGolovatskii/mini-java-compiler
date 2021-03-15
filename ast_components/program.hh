#ifndef COMPILER_PROGRAM_HH
#define COMPILER_PROGRAM_HH

#include "declarations/class_declaration.hh"
#include <memory>
#include <vector>

class TProgram : public INode {
public:
    explicit TProgram(TClassDeclarationList&& classDeclarations) : ClassDeclarations_(std::move(classDeclarations)) {}
    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }

    TClassDeclarationList& ClassDeclarations() {
        return ClassDeclarations_;
    }

private:
    TClassDeclarationList ClassDeclarations_;
};

using TProgramPtr = std::unique_ptr<TProgram>;

#endif//COMPILER_PROGRAM_HH
