#pragma once

#include "llvm/IR/Attributes.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Verifier.h"
#include <llvm/IR/Instructions.h>

#include <llvm/IR/Verifier.h>

#include "base_builder.hh"
#include "scope_table.hh"
#include "value_builder.hh"

class TFunctionRealizationBuilder : public TBaseBuilder {
public:
    explicit TFunctionRealizationBuilder(TBaseBuilder& base, const std::string& className,
                                         const std::string& functionName)
        : TBaseBuilder(base), ClassName_(className), Function_(FunctionTable.Get(functionName)) {}

    void Visit(struct TMemberMethodDeclaration* declaration) override {
        ScopeTable_.BeginScope("Arguments");

        BasicBlock_ = llvm::BasicBlock::Create(Context, "Entry", Function_);
        ArgsToScope_(declaration);


        declaration->Statements()->Accept(this);

        if (BasicBlock_->getTerminator() == nullptr) {
            if (TTypeResolver{*this}.Accept(declaration->ReturnType())->isVoidTy()) {
                llvm::ReturnInst::Create(Context, BasicBlock_);
            } else {
                throw std::logic_error{"No return statement"};
            }
        }

        ScopeTable_.EndScope();

        llvm::verifyFunction(*Function_);
    }

    void Visit(struct TStatementList* list) override {
        ScopeTable_.BeginScope();
        for (auto& stat : *list) {
            stat->Accept(this);
        }
        ScopeTable_.EndScope();
    }


    void Visit(struct TAssertionStatement* statement) override {
        TValueBuilder ValueBuilder{*this, ClassName_, ScopeTable_, BasicBlock_};
        auto* result = ValueBuilder.Accept(statement->Expression())->Load(BasicBlock_);
        if (result->getType() != llvm::Type::getInt1Ty(Context)) {
            throw std::logic_error{"unexpected type"};
        }

        llvm::BasicBlock* FailBB = llvm::BasicBlock::Create(Context, "Fail", Function_);
        llvm::BasicBlock* OkBB   = llvm::BasicBlock::Create(Context, "Ok", Function_);


        llvm::BranchInst::Create(OkBB, FailBB, result, BasicBlock_);

        llvm::FunctionType* exitType =
                llvm::FunctionType::get(llvm::Type::getVoidTy(Context), {llvm::Type::getInt32Ty(Context)}, false);

        auto exitFunction = Module.getOrInsertFunction("exit", exitType);

        llvm::CallInst::Create(exitFunction, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(Context), 1)}, "", FailBB);

        new llvm::UnreachableInst(Context, FailBB);

        BasicBlock_ = OkBB;
    }
    void Visit(struct TWhileStatement* statement) override {
        TValueBuilder ValueBuilder{*this, ClassName_, ScopeTable_, BasicBlock_};
        auto* cond = ValueBuilder.Accept(statement->Condition())->Load(BasicBlock_);

        auto* bodyBB     = llvm::BasicBlock::Create(Context, "body", Function_);
        auto* continueBB = llvm::BasicBlock::Create(Context, "continue", Function_);

        llvm::BranchInst::Create(bodyBB, continueBB, cond, BasicBlock_);

        CheckoutBB(bodyBB);
        statement->Statement()->Accept(this);
        auto* cond2 = ValueBuilder.Accept(statement->Condition())->Load(BasicBlock_);
        llvm::BranchInst::Create(bodyBB, continueBB, cond2, BasicBlock_);

        CheckoutBB(continueBB);
    }

    void Visit(struct TReturnStatement* statement) override {
        TValueBuilder ValueBuilder{*this, ClassName_, ScopeTable_, BasicBlock_};
        auto value = ValueBuilder.Accept(statement->Expression());
        llvm::ReturnInst::Create(Context, value->Load(BasicBlock_), BasicBlock_);
    }

    void Visit(struct TAssignmentStatement* statement) override {
        TValueBuilder ValueBuilder{*this, ClassName_, ScopeTable_, BasicBlock_};
        auto lvalue = ValueBuilder.Accept(statement->Lvalue());
        auto value  = ValueBuilder.Accept(statement->Expression());

        lvalue->Store(value.get(), BasicBlock_);
    }

    void Visit(struct TVariableDeclarationStatement* statement) override {
        TTypeResolver typeResolver{*this};

        auto* type = typeResolver.Accept(statement->Variable().Type());
        auto* ptr  = new llvm::AllocaInst(type, 0, statement->Variable().Name(), BasicBlock_);
        ScopeTable_.AddVariable(statement->Variable().Name(), TLocalVariable::Create(ptr, type));
    }

    void Visit(struct TMethodInvocationStatement* statement) override {
        TValueBuilder ValueBuilder{*this, ClassName_, ScopeTable_, BasicBlock_};
        ValueBuilder.Accept(statement->Method());// Ignore result :)
    }

    void Visit(struct TIfElseStatement* statement) override {
        TValueBuilder ValueBuilder{*this, ClassName_, ScopeTable_, BasicBlock_};
        auto* expr     = ValueBuilder.Accept(statement->Condition())->Load(BasicBlock_);
        auto* ifCase   = llvm::BasicBlock::Create(Context, "if", Function_);
        auto* elseCase = llvm::BasicBlock::Create(Context, "else", Function_);
        auto* cont     = llvm::BasicBlock::Create(Context, "continue", Function_);

        llvm::BranchInst::Create(ifCase, elseCase, expr, BasicBlock_);

        CheckoutBB(ifCase);
        statement->Statement()->Accept(this);
        CheckoutBB(elseCase);
        statement->ElseStatement()->Accept(this);
        CheckoutBB(cont);
    }

    void Visit(struct TIfStatement* statement) override {
        TValueBuilder ValueBuilder{*this, ClassName_, ScopeTable_, BasicBlock_};
        auto* expr   = ValueBuilder.Accept(statement->Condition())->Load(BasicBlock_);
        auto* ifCase = llvm::BasicBlock::Create(Context, "if", Function_);
        auto* cont   = llvm::BasicBlock::Create(Context, "continue", Function_);

        llvm::BranchInst::Create(ifCase, cont, expr, BasicBlock_);

        CheckoutBB(ifCase);
        statement->Statement()->Accept(this);
        CheckoutBB(cont);
    }

private:
    void CheckoutBB(llvm::BasicBlock* newBB) {
        if (!BasicBlock_->getTerminator()) {
            llvm::BranchInst::Create(newBB, BasicBlock_);
        }
        BasicBlock_ = newBB;
    }

    void ArgsToScope_(TMemberMethodDeclaration* declaration) {
        size_t offset = 0;
        auto& args    = declaration->Signature().Arguments();
        if (args.size() < Function_->arg_size()) {
            offset     = 1;
            auto* arg  = Function_->getArg(0);
            auto* type = arg->getType();

            auto* allocaInst = new llvm::AllocaInst(type, 0, "this", BasicBlock_);
            new llvm::StoreInst(arg, allocaInst, BasicBlock_);
            ScopeTable_.AddVariable("this", TLocalVariable::Create(allocaInst, type));
        }

        for (size_t i = offset; i < Function_->arg_size(); ++i) {
            auto* arg  = Function_->getArg(i);
            auto* type = arg->getType();
            auto& name = args[i - offset].Name();

            auto* allocaInst = new llvm::AllocaInst(type, 0, name, BasicBlock_);
            new llvm::StoreInst(arg, allocaInst, BasicBlock_);
            ScopeTable_.AddVariable(name, TLocalVariable::Create(allocaInst, type));
        }
    }

private:
    TScopeTable<IValuePtr> ScopeTable_;
    const std::string& ClassName_;
    llvm::Function* Function_;
    llvm::BasicBlock* BasicBlock_ = nullptr;
};

class TClassFunctionsRealizationBuilder : public TBaseBuilder {
public:
    explicit TClassFunctionsRealizationBuilder(TBaseBuilder& base, const std::string& name)
        : TBaseBuilder(base), ClassName_(name) {}

    void Visit(struct TClassMemberDeclarationList* list) override {
        for (auto& decl : *list) {
            decl->Accept(this);
        }
    }

    void Visit(struct TMemberMethodDeclaration* declaration) override {
        auto funcName = std::string(ClassName_) + "#" + declaration->Signature().Name();

        TFunctionRealizationBuilder builder{*this, ClassName_, funcName};
        declaration->Accept(&builder);
    }

    void Visit(struct TMemberVariableDeclaration* declaration) override {
        // Do nothing
    }

private:
    const std::string& ClassName_;
};

class TFunctionsRealizationBuilder : public TBaseBuilder {
public:
    explicit TFunctionsRealizationBuilder(TBaseBuilder& base) : TBaseBuilder(base) {}

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
        TClassFunctionsRealizationBuilder builder{*this, declaration->ClassName()};
        declaration->Members()->Accept(&builder);
    }
};
