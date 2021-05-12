#pragma once

#include <memory>
#include <utility>

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Value.h"


class IValue {
public:
    virtual llvm::Value* Load(llvm::BasicBlock* bb)         = 0;
    virtual void Store(IValue* value, llvm::BasicBlock* bb) = 0;

    virtual ~IValue() = default;
};


using IValuePtr = std::shared_ptr<IValue>;


class TLLVMValue : public IValue {
public:
    static IValuePtr Create(llvm::Value* value) {
        return std::make_shared<TLLVMValue>(value);
    }

    explicit TLLVMValue(llvm::Value* value) : Value_(value) {}

    llvm::Value* Load(llvm::BasicBlock* bb) override {
        return Value_;
    }

    void Store(IValue* value, llvm::BasicBlock* bb) override {
        throw std::logic_error{"unable to store rvalue"};
    }

private:
    llvm::Value* Value_;
};


using TLLVMValuePtr = std::shared_ptr<TLLVMValue>;


class TLocalVariable : public IValue {
public:
    static IValuePtr Create(llvm::Value* ptr, llvm::Type* type) {
        return std::make_shared<TLocalVariable>(ptr, type);
    }

    explicit TLocalVariable(llvm::Value* ptr, llvm::Type* type) : Ptr_(ptr), Type_(type) {}

    llvm::Value* Load(llvm::BasicBlock* bb) override {
        return new llvm::LoadInst(Type_, Ptr_, "", bb);
    }

    void Store(IValue* value, llvm::BasicBlock* bb) override {
        auto* loaded = value->Load(bb);
        new llvm::StoreInst(loaded, Ptr_, bb);
    }

private:
    llvm::Value* Ptr_;
    llvm::Type* Type_;
};


class TPointer : public IValue {
public:
    static IValuePtr Create(llvm::Instruction* ptr, llvm::Type* type) {
        return std::make_shared<TPointer>(ptr, type);
    }

    explicit TPointer(llvm::Instruction* ptr, llvm::Type* type) : Ptr_(ptr), Type_(type) {}

    llvm::Value* Load(llvm::BasicBlock* bb) override {
        return Ptr_;
    }

    void Store(IValue* value, llvm::BasicBlock* bb) override {
        throw std::logic_error{"unable to store class"};
    }

private:
    llvm::Instruction* Ptr_;
    llvm::Type* Type_;
};


class TPointerIndexValue : public IValue {
public:
    static IValuePtr Create(llvm::Value* ptr, llvm::Type* type, const std::vector<llvm::Value*>& index) {
        return std::make_shared<TPointerIndexValue>(ptr, type, index);
    }

    TPointerIndexValue(llvm::Value* ptr, llvm::Type* type, std::vector<llvm::Value*> index)
        : Ptr_(ptr), Type_(type), Index_(std::move(index)) {}

    llvm::Value* Load(llvm::BasicBlock* bb) override {
        auto* elementPtr = llvm::GetElementPtrInst::Create(Type_, Ptr_, Index_, "", bb);

        return new llvm::LoadInst(elementPtr->getResultElementType(), elementPtr, "", bb);
    }

    void Store(IValue* value, llvm::BasicBlock* bb) override {
        auto* loaded     = value->Load(bb);
        auto* elementPtr = llvm::GetElementPtrInst::Create(Type_, Ptr_, Index_, "", bb);

        new llvm::StoreInst(loaded, elementPtr, bb);
    }

private:
    llvm::Value* Ptr_;
    llvm::Type* Type_;
    std::vector<llvm::Value*> Index_;
};