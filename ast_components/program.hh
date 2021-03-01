#ifndef COMPILER_PROGRAM_HH
#define COMPILER_PROGRAM_HH

#include "class_declaration.hh"
#include <memory>
#include <vector>

class TProgram {
public:
    TProgram(TClassDeclarationPtr&& mainClass, TClassDeclarationList&& classDeclarations)
        : MainClass_(std::move(mainClass)), ClassDeclarations_(std::move(classDeclarations)) {}

private:
    TClassDeclarationPtr MainClass_;
    TClassDeclarationList ClassDeclarations_;
};

using TProgramPtr = std::unique_ptr<TProgram>;

#endif//COMPILER_PROGRAM_HH
