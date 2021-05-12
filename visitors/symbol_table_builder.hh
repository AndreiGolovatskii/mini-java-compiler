#pragma once

#include <variant>

#include "symbol_table.hh"
#include "template_visitor.hh"
#include "types.hh"


class TSymbolTableBuilder : public TTemplateVisitor<std::unique_ptr<IType>> {
public:
    void Visit(TMemberVariableDeclaration* declaration) override {
        auto type = Accept(declaration->Variable().Type());
        Table_.Get(CurrentClass_)->AddVariable(declaration->Variable().Name(), std::move(type));
    }
    void Visit(TMemberMethodDeclaration* declaration) override {
        std::vector<TArgument> args;
        std::for_each(declaration->Signature().Arguments().begin(), declaration->Signature().Arguments().end(),
                      [this, &args](const TVariable& arg) mutable {
                          args.emplace_back(arg.Name(), Accept(arg.Type()));
                      });

        Table_.Get(CurrentClass_)
                ->AddMethod(declaration->Signature().Name(),
                            std::make_unique<TMethodSpecification>(Accept(declaration->ReturnType()), std::move(args),
                                                                   declaration->IsStatic()));
    }
    void Visit(TIntTypeNode* type) override {
        Return(std::make_unique<TIntegerType>());
    }
    void Visit(TBooleanTypeNode* type) override {
        Return(std::make_unique<TBooleanType>());
    }
    void Visit(TVoidTypeNode* type) override {
        Return(std::make_unique<TVoidType>());
    }
    void Visit(TIdentifierTypeNode* type) override {
        Return(std::make_unique<TClassPtrType>(Table_.Get(type->Identifier()).get()));
    }
    void Visit(TArrayTypeNode* node) override {
        Return(std::make_unique<TArrayType>());
    }
    void Visit(TClassMemberDeclarationList* list) override {
        std::for_each(list->begin(), list->end(), [this](const auto& it) {
            it->Accept(this);
        });
    }
    void Visit(TClassDeclaration* declaration) override {
        CurrentClass_ = declaration->ClassName();
        Accept(declaration->Members());
    }
    void Visit(TClassDeclarationList* list) override {
        std::for_each(list->begin(), list->end(), [this](const auto& it) {
            Table_.Add(it->ClassName(), std::make_unique<TClassSpecification>());
        });
        std::for_each(list->begin(), list->end(), [this](const auto& it) {
            it->Accept(this);
        });
    }
    void Visit(TProgram* program) override {
        Accept(program->ClassDeclarations());
    }

    TSymbolTable<>& SymbolTable() {
        return Table_;
    }

private:
    TSymbolTable<> Table_;
    std::string CurrentClass_;
};