#pragma once

#include "llvm/IR/Type.h"

#include "base_builder.hh"
#include "template_visitor.hh"

class TTypeResolver : public TTemplateVisitor<llvm::Type*> {
public:
    explicit TTypeResolver(TBaseBuilder& base) : Base(base) {}

    void Visit(struct TIntTypeNode* type) override {
        Return(llvm::Type::getInt32Ty(Base.Context));
    }

    void Visit(struct TBooleanTypeNode* type) override {
        Return(llvm::Type::getInt1Ty(Base.Context));
    }

    void Visit(struct TVoidTypeNode* type) override {
        Return(llvm::Type::getVoidTy(Base.Context));
    }

    void Visit(struct TIdentifierTypeNode* type) override {
        Return(llvm::PointerType::get(Base.ClassTable.Get(type->Identifier()), 0));
    }

    void Visit(struct TArrayTypeNode* node) override {
        Return(llvm::PointerType::get(Accept(node->Type()), 0));
    }

private:
    TBaseBuilder& Base;
};
