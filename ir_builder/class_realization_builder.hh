#pragma once

#include "base_builder.hh"
#include "type_resolver.hh"


class TClassRealizationBuilder : public TBaseBuilder {
public:
    explicit TClassRealizationBuilder(TBaseBuilder& base, const std::string& name)
        : TBaseBuilder(base), className_(name) {}

    void Visit(struct TClassMemberDeclarationList* list) override {
        for (auto& decl : *list) {
            decl->Accept(this);
        }

        ClassTable.Get(className_)->setBody(Members_);
    }
    void Visit(struct TMemberMethodDeclaration* declaration) override {
        // Do nothing
    }
    void Visit(struct TMemberVariableDeclaration* declaration) override {
        auto type = TTypeResolver{*this}.Accept(declaration->Variable().Type());
        MemberTable.Add(className_ + "#" + declaration->Variable().Name(), Members_.size());
        Members_.push_back(type);
    }

private:
    const std::string& className_;
    std::vector<llvm::Type*> Members_;
};

class TClassesRealizationBuilder : public TBaseBuilder {
public:
    explicit TClassesRealizationBuilder(TBaseBuilder& base) : TBaseBuilder(base) {}

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
        TClassRealizationBuilder builder{*this, declaration->ClassName()};

        declaration->Members()->Accept(&builder);
    }
};
