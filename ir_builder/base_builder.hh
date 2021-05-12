#pragma once

#include <memory>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include "partial_visitor.hh"
#include "scope_table.hh"
#include "symbol_table.hh"
#include "value.hh"

class TBaseBuilder : public TPartialVisitor {
private:
    using ClassTableType    = TSymbolTable<llvm::StructType*>;
    using MemberTableType   = TSymbolTable<size_t>;
    using FunctionTableType = TSymbolTable<llvm::Function*>;

public:
    TBaseBuilder(llvm::LLVMContext& context, llvm::Module& Module)
        : ClassTablePtr_(std::make_shared<ClassTableType>()), FunctionTablePtr_(std::make_shared<FunctionTableType>()),
          MemberTablePtr_(std::make_shared<MemberTableType>()), Context(context), Module(Module),
          ClassTable(*ClassTablePtr_), FunctionTable(*FunctionTablePtr_), MemberTable(*MemberTablePtr_) {}


private:
    std::shared_ptr<ClassTableType> ClassTablePtr_;
    std::shared_ptr<FunctionTableType> FunctionTablePtr_;
    std::shared_ptr<MemberTableType> MemberTablePtr_;

public:
    llvm::LLVMContext& Context;
    llvm::Module& Module;
    ClassTableType& ClassTable;
    FunctionTableType& FunctionTable;
    MemberTableType& MemberTable;
};
