#ifndef COMPILER_NAIVE_INTERPRETER_HH
#define COMPILER_NAIVE_INTERPRETER_HH

#include <exception>
#include <functional>
#include <string>
#include <unordered_map>
#include <variant>

#include "ast_components.hh"
#include "i_visitor.hh"

class TNaiveInterpreter : public IVisitor {
public:
    explicit TNaiveInterpreter(std::ostream& out) : Out_(out), ReturnValue_(-1) {}
    void Visit(struct TMemberVariableDeclaration* declaration) override {
        throw std::logic_error{"unsupported"};
    }
    void Visit(struct TIdentifierTypeNode* type) override {
        throw std::logic_error{"unsupported"};
    }
    void Visit(struct TMethodInvocation* invocation) override {
        throw std::logic_error{"unsupported"};
    }
    void Visit(struct TMethodInvocationExpression* expression) override {
        throw std::logic_error{"unsupported"};
    }
    void Visit(struct TAndExpression* expression) override {
        BinaryExpression(expression, std::logical_and<>());
    }
    void Visit(struct TAssertionStatement* statement) override {
        statement->Expression()->Accept(this);
        if (!GetReturnValue_()) {
            throw std::runtime_error{"Assertion failed"};
        }
    }
    void Visit(struct TAssignmentStatement* statement) override {
        statement->Expression()->Accept(this);
        int value = GetReturnValue_();
        statement->Lvalue()->Accept(this);
        std::get<lvalue>(ReturnValue_)->second = value;
    }
    void Visit(struct TBooleanExpression* expression) override {
        ReturnValue_ = expression->GetValue();
    }
    void Visit(struct TClassDeclaration* declaration) override {
        declaration->Members()->Accept(this);
    }
    void Visit(struct TClassMemberDeclarationList* list) override {
        for (const auto& member : *list) {
            member->Accept(this);
        }
    }
    void Visit(struct TDivExpression* expression) override {
        BinaryExpression(expression, std::divides<>());
    }
    void Visit(struct TEqExpression* expression) override {
        BinaryExpression(expression, std::equal_to<>());
    }
    void Visit(struct TNEqExpression* expression) override {
        BinaryExpression(expression, std::not_equal_to<>());
    }
    void Visit(struct TExpressionList* list) override {
        for (const auto& expression : *list) {
            expression->Accept(this);
        }
    }
    void Visit(struct TFieldInvocation* invocation) override {
        throw std::logic_error{"unsupported"};
    }
    void Visit(struct TFieldInvocationExpression* expression) override {
        throw std::logic_error{"unsupported"};
    }
    void Visit(struct TGeExpression* expression) override {
        BinaryExpression(expression, std::greater<>());
    }
    void Visit(struct TGeqExpression* expression) override {
        BinaryExpression(expression, std::greater_equal<>());
    }
    void Visit(struct TIdentifierExpression* expression) override {
        ReturnValue_ = Variables_.find(expression->Identifier());
    }

    void Visit(struct TIndexExpression* expression) override {
        throw std::logic_error{"unsupported"};
    }
    void Visit(struct TIntExpression* expression) override {
        ReturnValue_ = expression->GetValue();
    }
    void Visit(struct TLeExpression* expression) override {
        BinaryExpression(expression, std::less<>());
    }
    void Visit(struct TLeqExpression* expression) override {
        BinaryExpression(expression, std::less_equal<>());
    }
    void Visit(struct TVoidTypeNode* type) override {
        throw std::logic_error{"unsupported"};
    }
    void Visit(struct TIntTypeNode* type) override {}
    void Visit(struct TArrayTypeNode* node) override {}
    void Visit(struct TBooleanTypeNode* type) override {}
    void Visit(struct TThisExpression* expression) override {
        throw std::logic_error{"unsupported"};
    }
    void Visit(struct TMemberMethodDeclaration* declaration) override {
        if (declaration->IsStatic() && declaration->Signature().Name() == "main") {
            try {
                declaration->Statements()->Accept(this);
            } catch (TReturnException& ret) {
            }
            ReturnValue_ = 0;
            Variables_.clear();
        }
    }
    void Visit(struct TClassDeclarationList* list) override {
        for (const auto& cls : *list) {
            cls->Accept(this);
        }
    }
    void Visit(struct TProgram* program) override {
        program->ClassDeclarations()->Accept(this);
    }
    void Visit(struct TSubExpression* expression) override {
        BinaryExpression(expression, std::minus<>());
    }
    void Visit(struct TModExpression* expression) override {
        BinaryExpression(expression, std::modulus<>());
    }
    void Visit(struct TOrExpression* expression) override {
        BinaryExpression(expression, std::logical_or<>());
    }
    void Visit(struct TSumExpression* expression) override {
        BinaryExpression(expression, std::plus<>());
    }
    void Visit(struct TReturnStatement* statement) override {
        throw TReturnException{};
    }
    void Visit(struct TNotExpression* expression) override {
        expression->Expression()->Accept(this);
        ReturnValue_ = !GetReturnValue_();
    }
    void Visit(struct TPrintlnStatement* statement) override {
        statement->Expression()->Accept(this);
        Out_ << GetReturnValue_() << std::endl;
    }
    void Visit(struct TMulExpression* expression) override {
        BinaryExpression(expression, std::multiplies<>());
    }
    void Visit(struct TLengthExpression* expression) override {
        throw std::logic_error{"unsupported"};
    }
    void Visit(struct TVariableDeclarationStatement* statement) override {
        const std::string& name = statement->Variable().Name();
        Variables_[name]        = 0;
    }
    void Visit(struct TMethodInvocationStatement* statement) override {
        throw std::logic_error{"unsupported"};
    }
    void Visit(struct TStatementList* list) override {
        for (const auto& statement : *list) {
            statement->Accept(this);
        }
    }
    void Visit(struct TNewExpression* expression) override {
        throw std::logic_error{"unsupported"};
    }
    void Visit(struct TNewArrayExpression* expression) override {
        throw std::logic_error{"unsupported"};
    }
    void Visit(struct TIfElseStatement* statement) override {
        statement->Condition()->Accept(this);
        if (GetReturnValue_()) {
            statement->Statement()->Accept(this);
        } else {
            statement->ElseStatement()->Accept(this);
        }
    }
    void Visit(struct TIfStatement* statement) override {
        statement->Condition()->Accept(this);
        if (GetReturnValue_()) {
            statement->Statement()->Accept(this);
        }
    }
    void Visit(struct TWhileStatement* statement) override {
        statement->Condition()->Accept(this);
        while (GetReturnValue_()) {
            statement->Statement()->Accept(this);
            statement->Condition()->Accept(this);
        }
    }
    void Visit(struct TUnaryMinusExpression* expression) override {
        expression->Expression()->Accept(this);
        ReturnValue_ = -GetReturnValue_();
    }


private:
    struct TReturnException : public std::exception {};

    int GetReturnValue_() {
        return std::visit(
                [](auto&& arg) {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, int>) {
                        return arg;
                    } else {
                        return arg->second;
                    }
                },
                ReturnValue_);
    }


    void BinaryExpression(TBinaryExpression* expression, const std::function<int(int, int)>& fun) {
        expression->Lhs()->Accept(this);
        int r1 = GetReturnValue_();
        expression->Rhs()->Accept(this);
        int r2       = GetReturnValue_();
        ReturnValue_ = fun(r1, r2);
    }

private:
    std::unordered_map<std::string, int> Variables_;
    using lvalue = std::unordered_map<std::string, int>::iterator;
    std::variant<int, lvalue> ReturnValue_;
    std::ostream& Out_;
};

#endif//COMPILER_NAIVE_INTERPRETER_HH
