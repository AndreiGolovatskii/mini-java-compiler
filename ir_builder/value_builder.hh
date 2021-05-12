#pragma once

#include "llvm/IR/Value.h"

#include "base_builder.hh"
#include "scope_table.hh"
#include "template_visitor.hh"

#include "value.hh"

class TValueBuilder : public TTemplateVisitor<IValuePtr> {
public:
    TValueBuilder(TBaseBuilder& base, const std::string& className, TScopeTable<IValuePtr>& scopeTable,
                  llvm::BasicBlock*& basicBlock)
        : Base_(base), ClassName_(className), ScopeTable_(scopeTable), BasicBlock_(basicBlock){};

    void Visit(struct TBooleanExpression* expression) override {
        Return(TLLVMValue::Create(
                llvm::ConstantInt::get(llvm::Type::getInt1Ty(Base_.Context), expression->GetValue())));
    }

    void Visit(struct TAndExpression* expression) override {
        BinaryExpr_(expression, llvm::BinaryOperator::And);
    }

    void Visit(struct TIntExpression* expression) override {
        Return(TLLVMValue::Create(
                llvm::ConstantInt::get(llvm::Type::getInt32Ty(Base_.Context), expression->GetValue())));
    }

    void Visit(struct TEqExpression* expression) override {
        ICmpExpr_(expression, llvm::ICmpInst::Predicate::ICMP_EQ);
    }

    void Visit(struct TNEqExpression* expression) override {
        ICmpExpr_(expression, llvm::ICmpInst::Predicate::ICMP_NE);
    }

    void Visit(struct TLeqExpression* expression) override {
        ICmpExpr_(expression, llvm::ICmpInst::Predicate::ICMP_SLE);
    }

    void Visit(struct TLeExpression* expression) override {
        ICmpExpr_(expression, llvm::ICmpInst::Predicate::ICMP_SLT);
    }

    void Visit(struct TGeExpression* expression) override {
        ICmpExpr_(expression, llvm::ICmpInst::Predicate::ICMP_SGT);
    }

    void Visit(struct TGeqExpression* expression) override {
        ICmpExpr_(expression, llvm::ICmpInst::Predicate::ICMP_SGE);
    }

    void Visit(struct TIdentifierExpression* expression) override {
        if (ScopeTable_.HasVariable(expression->Identifier())) {
            Return(ScopeTable_.Variable(expression->Identifier()));
        } else if (Base_.MemberTable.Has(ClassName_ + "#" + expression->Identifier())) {
            auto field =
                    std::make_unique<TFieldInvocation>(std::make_unique<TThisExpression>(), expression->Identifier());
            Return(Accept(field.get()));
        } else {
            throw std::logic_error{"Undeclared variable"};
        }
    }

    void Visit(struct TMethodInvocationExpression* expression) override {
        Return(Accept(expression->Invocation()));
    }

    void Visit(struct TMethodInvocation* invocation) override {
        auto className = ClassNameFromInvocation_(invocation);
        std::vector<llvm::Value*> args;

        llvm::Function* func;
        if (!className.has_value()) {
            auto self     = Accept(invocation->Expression());
            auto* selfPtr = self->Load(BasicBlock_);
            className     = std::string(
                    llvm::dyn_cast<llvm::PointerType>(selfPtr->getType())->getElementType()->getStructName());

            func = Base_.FunctionTable.Get(className.value() + "#" + invocation->Method());

            if (func->arg_size() > invocation->Arguments()->size()) {
                args.push_back(selfPtr);
            }

        } else {
            func = Base_.FunctionTable.Get(className.value() + "#" + invocation->Method());
        }

        for (auto& expr : *invocation->Arguments()) {
            args.push_back(Accept(expr.get())->Load(BasicBlock_));
        }

        auto* callInst = llvm::CallInst::Create(func, args, "", BasicBlock_);
        callInst->setTailCall();

        Return(TLLVMValue::Create(callInst));
    }


    void Visit(struct TThisExpression* expression) override {
        Return(ScopeTable_.Variable("this"));
    }

    void Visit(struct TSumExpression* expression) override {
        BinaryExpr_(expression, llvm::Instruction::BinaryOps::Add);
    }

    void Visit(struct TSubExpression* expression) override {
        BinaryExpr_(expression, llvm::Instruction::BinaryOps::Sub);
    }

    void Visit(struct TModExpression* expression) override {
        BinaryExpr_(expression, llvm::Instruction::BinaryOps::SRem);
    }

    void Visit(struct TMulExpression* expression) override {
        BinaryExpr_(expression, llvm::Instruction::BinaryOps::Mul);
    }

    void Visit(struct TDivExpression* expression) override {
        BinaryExpr_(expression, llvm::Instruction::BinaryOps::SDiv);
    }

    void Visit(struct TNotExpression* expression) override {
        auto* res = Accept(expression->Expression())->Load(BasicBlock_);
        Return(TLLVMValue::Create(llvm::BinaryOperator::CreateNot(res, "", BasicBlock_)));
    }

    void Visit(struct TNewExpression* expression) override {
        auto* type       = TTypeResolver{Base_}.Accept(expression->Type());
        auto* structType = llvm::dyn_cast<llvm::PointerType>(type)->getElementType();
        auto* mallocInst =
                llvm::CallInst::CreateMalloc(BasicBlock_, llvm::Type::getInt64Ty(Base_.Context), structType,
                                             llvm::ConstantExpr::getSizeOf(structType), nullptr, nullptr, "");
        BasicBlock_->getInstList().push_back(mallocInst);// :/
        Return(TPointer::Create(mallocInst, structType));
    }

    void Visit(struct TNewArrayExpression* expression) override {
        TTypeResolver typeResolver{Base_};
        auto* type      = typeResolver.Accept(expression->Type());
        auto* sizeValue = Accept(expression->Size())->Load(BasicBlock_);

        auto* mallocInst = llvm::CallInst::CreateMalloc(BasicBlock_, llvm::Type::getInt64Ty(Base_.Context), type,
                                                        llvm::ConstantExpr::getSizeOf(type), sizeValue, nullptr, "");
        BasicBlock_->getInstList().push_back(mallocInst);// :/
        Return(TPointer::Create(mallocInst, type));
    }

    void Visit(struct TIndexExpression* expression) override {
        auto* ptr   = Accept(expression->Expression())->Load(BasicBlock_);
        auto* type  = llvm::dyn_cast<llvm::PointerType>(ptr->getType())->getElementType();
        auto* index = Accept(expression->Index())->Load(BasicBlock_);

        auto* indexToI64 =
                llvm::CastInst::CreateIntegerCast(index, llvm::Type::getInt64Ty(Base_.Context), true, "", BasicBlock_);
        Return(TPointerIndexValue::Create(ptr, type, {indexToI64}));
    }

    void Visit(struct TFieldInvocation* invocation) override {
        auto* ptr = Accept(invocation->Expression())->Load(BasicBlock_);

        auto* type            = llvm::dyn_cast<llvm::PointerType>(ptr->getType())->getElementType();
        std::string className = std::string(type->getStructName());

        int index = Base_.MemberTable.Get(className + "#" + invocation->Identifier());
        Return(TPointerIndexValue::Create(
                ptr, type,
                {llvm::ConstantInt::get(llvm::Type::getInt64Ty(Base_.Context), 0, false),
                 llvm::ConstantInt::get(llvm::Type::getInt32Ty(Base_.Context), index, false)}));
    }

    void Visit(struct TFieldInvocationExpression* expression) override {
        Return(Accept(expression->Invocation()));
    }

private:
    std::optional<std::string> ClassNameFromInvocation_(TMethodInvocation* invocation) {
        auto* identifier = dynamic_cast<TIdentifierExpression*>(invocation->Expression());
        if (identifier and Base_.ClassTable.Has(identifier->Identifier())) {
            return identifier->Identifier();
        }
        auto* thisPtr = dynamic_cast<TThisExpression*>(invocation->Expression());
        if (thisPtr) {
            return ClassName_;
        }
        return std::nullopt;
    }

    void BinaryExpr_(TBinaryExpression* expression, llvm::Instruction::BinaryOps op) {
        auto* lhs = Accept(expression->Lhs())->Load(BasicBlock_);
        auto* rhs = Accept(expression->Rhs())->Load(BasicBlock_);

        Return(TLLVMValue::Create(llvm::BinaryOperator::Create(op, lhs, rhs, "", BasicBlock_)));
    }

    void ICmpExpr_(TBinaryExpression* expression, llvm::ICmpInst::Predicate predicate) {
        auto* lsh = Accept(expression->Lhs())->Load(BasicBlock_);
        auto* rhs = Accept(expression->Rhs())->Load(BasicBlock_);

        Return(TLLVMValue::Create(
                llvm::CmpInst::Create(llvm::Instruction::OtherOps::ICmp, predicate, lsh, rhs, "", BasicBlock_)));
    }

    TBaseBuilder& Base_;
    const std::string& ClassName_;
    TScopeTable<IValuePtr>& ScopeTable_;
    llvm::BasicBlock*& BasicBlock_;
};