#pragma once

#include "base_builder.hh"



class TClassesDeclarationBuilder : public TBaseBuilder {
public:
    explicit TClassesDeclarationBuilder(TBaseBuilder& base) : TBaseBuilder(base) {}

    void Visit(struct TProgram* program) override {
        program->ClassDeclarations()->Accept(this);
    }

    void Visit(struct TClassDeclarationList* list) override {
        for (auto& decl : *list) {
            decl->Accept(this);
        }
    }
    void Visit(struct TClassDeclaration* declaration) override {
        assert(declaration->Extends() == "object"); // TODO
        auto StructPtr = llvm::StructType::create(Context, declaration->ClassName());
        StructPtr->setName(declaration->ClassName());
        ClassTable.Add(declaration->ClassName(), StructPtr);
    }

};
