#pragma once


#include "base_builder.hh"

class TClassFunctionsDeclarationBuilder : public TBaseBuilder {
public:
    TClassFunctionsDeclarationBuilder(TBaseBuilder& base, const std::string& name)
        : TBaseBuilder(base), ClassName_(name) {}

    void Visit(struct TClassMemberDeclarationList* list) override {
        for (auto& decl : *list) {
            decl->Accept(this);
        }
    }

    void Visit(struct TMemberMethodDeclaration* declaration) override {
        auto arguments = ConstructArguments_(declaration);

        llvm::FunctionType* funcType =
                llvm::FunctionType::get(TypeResolver.Accept(declaration->ReturnType()), arguments, false);

        auto funcName        = std::string(ClassName_) + "#" + declaration->Signature().Name();
        llvm::Function* func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, funcName, Module);

        FunctionTable.Add(funcName, func);
    }

    void Visit(struct TMemberVariableDeclaration* declaration) override {
        // Do nothing
    }

private:
    std::vector<llvm::Type*> ConstructArguments_(TMemberMethodDeclaration* declaration) {
        std::vector<llvm::Type*> arguments;

        if (!declaration->IsStatic()) {
            arguments.push_back(llvm::PointerType::get(ClassTable.Get(ClassName_), 0));// "this" argument
        }

        for (auto& arg : declaration->Signature().Arguments()) {
            arguments.push_back(TypeResolver.Accept(arg.Type()));
        }

        return arguments;
    }

private:
    const std::string& ClassName_;
    TTypeResolver TypeResolver{*this};
};


class TFunctionsDeclarationBuilder : public TBaseBuilder {
public:
    explicit TFunctionsDeclarationBuilder(TBaseBuilder& base) : TBaseBuilder(base) {}

    void Visit(struct TProgram* program) override {
        program->ClassDeclarations()->Accept(this);
    }

    void Visit(struct TClassDeclarationList* list) override {
        for (auto& decl : *list) {
            decl->Accept(this);
        }
    }

    void Visit(struct TClassDeclaration* declaration) override {
        assert(declaration->Extends() == "object");// TODO
        TClassFunctionsDeclarationBuilder builder{*this, declaration->ClassName()};
        declaration->Members()->Accept(&builder);
    }
};