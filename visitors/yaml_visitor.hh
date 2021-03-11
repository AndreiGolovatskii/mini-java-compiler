#ifndef COMPILER_YAML_VISITOR_HH
#define COMPILER_YAML_VISITOR_HH

#include <iostream>

#include "yaml-cpp/yaml.h"

#include "ast_components.hh"
#include "i_visitor.hh"

class TYamlVisitor : public IVisitor {
public:
    void Visit(struct TAndExpression* expression) override {
        BinaryExpression_("and ", expression);
    }

    void Visit(struct TAssertionStatement* statement) override {
        YAML::Node result;
        result["kind"] = "assert statement";
        statement->Expression()->Accept(this);
        result["expresion"] = Return_;

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TAssignmentStatement* statement) override {
        YAML::Node result;
        result["kind"] = "assignment statement";
        statement->Expression()->Accept(this);
        result["expression"] = Return_;
        statement->Lvalue()->Accept(this);
        result["lvalue"] = Return_;

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TBooleanExpression* expression) override {
        ValueExpression_("boolean", expression);
    }
    void Visit(struct TClassDeclaration* declaration) override {
        YAML::Node result;
        result["kind"] = "class";
        result["name"] = declaration->ClassName();
        declaration->Members().Accept(this);
        result["members"] = Return_;

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TClassMemberDeclarationList* list) override {
        List_(list);
    }
    void Visit(struct TDivExpression* expression) override {
        BinaryExpression_("div", expression);
    }
    void Visit(struct TEqExpression* expression) override {
        BinaryExpression_("eq", expression);
    }
    void Visit(struct TExpressionList* list) override {
        List_(list);
    }
    void Visit(struct TFieldInvocation* invocation) override {
        YAML::Node result;
        result["kind"]       = "field invocation";
        result["identifier"] = invocation->Identifier();

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TFieldInvocationExpression* expression) override {
        YAML::Node result;
        result["kind"] = "field invocation expression";
        expression->Method()->Accept(this);
        result["invocation"] = Return_;

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TFieldInvocationIndexed* invocationIndexed) override {
        YAML::Node result;
        result["kind"] = "field invocation indexed";
        invocationIndexed->Index()->Accept(this);
        result["index"] = Return_;

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TGeExpression* expression) override {
        BinaryExpression_("ge", expression);
    }
    void Visit(struct TGeqExpression* expression) override {
        BinaryExpression_("geq", expression);
    }
    void Visit(struct TIdentifierExpression* expression) override {
        YAML::Node result;
        result["kind"]       = "identifier expression";
        result["identifier"] = expression->Identifier();

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TIfElseStatement* statement) override {
        YAML::Node result;
        result["kind"] = "if-else statement";

        statement->Condition()->Accept(this);
        result["condition"] = Return_;

        statement->Statement()->Accept(this);
        result["if statement"] = Return_;

        statement->ElseStatement()->Accept(this);
        result["else statement"] = Return_;

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TIfStatement* statement) override {
        YAML::Node result;
        result["kind"] = "if statement";

        statement->Condition()->Accept(this);
        result["condition"] = Return_;

        statement->Statement()->Accept(this);
        result["statement"] = Return_;

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TIndexExpression* expression) override {
        YAML::Node result;
        result["kind"] = "index expression";

        expression->Expression()->Accept(this);
        result["expression"] = Return_;

        expression->Index()->Accept(this);
        result["index"] = Return_;

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TIntExpression* expression) override {
        ValueExpression_("int", expression);
    }
    void Visit(struct TLeExpression* expression) override {
        BinaryExpression_("le", expression);
    }
    void Visit(struct TStatementList* list) override {
        List_(list);
    }
    void Visit(struct TLengthExpression* expression) override {
        YAML::Node result;
        result["kind"] = "length expression";

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TLeqExpression* expression) override {
        BinaryExpression_("leq", expression);
    }
    void Visit(struct TMemberMethodDeclaration* declaration) override {
        YAML::Node result;
        result["kind"]      = "method";
        result["is-static"] = declaration->IsStatic();
        result["name"]      = declaration->Signature().Name();

        declaration->ReturnType()->Accept(this);
        result["return-type"] = Return_;

        if (declaration->Signature().Arguments().empty()) {
            result["arguments"] = YAML::Null;
        } else {
            for (const auto& argument : declaration->Signature().Arguments()) {
                YAML::Node arg;
                argument.Type()->Accept(this);
                arg["name"] = argument.Name();
                arg["type"] = Return_;

                result["arguments"].push_back(arg);
            }
        }

        declaration->Statements()->Accept(this);
        result["statements"] = Return_;

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TMemberVariableDeclaration* declaration) override {
        YAML::Node result;
        result["kind"] = "member variable declaration";
        result["name"] = declaration->Variable().Name();

        declaration->Variable().Type()->Accept(this);
        result["variable-type"] = Return_;

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TMethodInvocation* invocation) override {
        YAML::Node result;
        result["kind"]   = "method invocation";
        result["method"] = invocation->Method();

        invocation->Expression()->Accept(this);
        result["expression"] = Return_;

        invocation->Arguments()->Accept(this);
        result["arguments"] = Return_;

        Return_.reset();
        Return_ = result;
    }

    void Visit(struct TMethodInvocationExpression* expression) override {
        YAML::Node result;
        result["kind"] = "method invocation expression";
        expression->Invocation()->Accept(this);
        result["invocation"] = Return_;

        Return_.reset();
        Return_ = result;
    }

    void Visit(struct TMethodInvocationStatement* statement) override {
        YAML::Node result;
        result["statement"] = "method invocation statement";

        statement->Method()->Accept(this);
        result["invocation"] = Return_;

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TModExpression* expression) override {
        BinaryExpression_("mod", expression);
    }
    void Visit(struct TMulExpression* expression) override {
        BinaryExpression_("mul", expression);
    }
    void Visit(struct TNewArrayExpression* expression) override {
        YAML::Node result;
        result["kind"] = "new array expression";

        expression->Type()->Accept(this);
        result["value-type"] = Return_;

        expression->Size()->Accept(this);
        result["size"] = Return_;

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TNewExpression* expression) override {
        YAML::Node result;
        result["kind"] = "new expression";

        expression->Type()->Accept(this);
        result["value-type"] = Return_;

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TNotExpression* expression) override {
        YAML::Node result;
        result["kind"] = "not expression";

        expression->Expression()->Accept(this);
        result["expression"] = Return_;

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TOrExpression* expression) override {
        BinaryExpression_("or", expression);
    }
    void Visit(struct TPrintlnStatement* statement) override {
        YAML::Node result;
        result["kind"] = "print statement";

        statement->Expression()->Accept(this);
        result["expression"] = Return_;

        Return_.reset();
        Return_ = result;
    }

    void Visit(struct TProgram* program) override {
        program->ClassDeclarations().Accept(this);
        Root_["Classes"] = Return_;
    }
    void Visit(struct TReturnStatement* statements) override {
        YAML::Node result;
        result["kind"] = "return statement";
        statements->Expression()->Accept(this);
        result["expression"] = Return_;

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TClassDeclarationList* list) override {
        List_(list);
    }
    void Visit(struct TSubExpression* expression) override {
        BinaryExpression_("sub", expression);
    }
    void Visit(struct TSumExpression* expression) override {
        BinaryExpression_("sum", expression);
    }
    void Visit(struct TThisExpression* expression) override {
        YAML::Node result;
        result["kind"] = "this expression";

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TVariableDeclarationStatement* statement) override {
        YAML::Node result;
        result["kind"] = "variable declaration statement";

        statement->Variable().Type()->Accept(this);
        result["variable-type"] = Return_;

        result["variable-name"] = statement->Variable().Name();

        Return_.reset();
        Return_ = result;
    }
    void Visit(struct TWhileStatement* statement) override {
        YAML::Node result;
        result["kind"] = "while statement";

        statement->Condition()->Accept(this);
        result["condition"] = Return_;

        statement->Statement()->Accept(this);
        result["statement"] = Return_;

        Return_.reset();
        Return_ = result;
    }

    void Visit(struct TIntType* type) override {
        Type_("int", type);
    }
    void Visit(struct TBooleanType* type) override {
        Type_("boolean", type);
    }
    void Visit(struct TVoidType* type) override {
        Type_("void", type);
    }
    void Visit(struct TIdentifierType* type) override {
        YAML::Node result;
        result["kind"]       = "identifier type";
        result["identifier"] = type->Identifier();
        result["is-array"]   = type->IsArray();

        Return_.reset();
        Return_ = result;
    }

    void Print(std::ostream& out) const {
        out << Root_;
    }
    void Visit(struct TUnaryMinusExpression* expression) override {
        YAML::Node result;
        result["kind"] = "unary minus expression";
        expression->Expression()->Accept(this);
        result["expression"] = Return_;

        Return_.reset();
        Return_ = result;
    }

private:
    YAML::Node Root_;
    YAML::Node Return_;

    template<typename T>
    void List_(T* list) {
        YAML::Node result;
        for (const auto& elem : *list) {
            elem->Accept(this);
            result.push_back(Return_);
        }
        Return_.reset();
        Return_ = result;
    }

    void BinaryExpression_(const std::string& prefix, TBinaryExpression* expression) {
        YAML::Node result;
        result["kind"] = prefix + " expression";
        expression->Lhs()->Accept(this);
        result["lhs"] = Return_;
        expression->Rhs()->Accept(this);
        result["rhs"] = Return_;

        Return_.reset();
        Return_ = result;
    }

    template<typename T>
    void ValueExpression_(const std::string& prefix, T* expression) {
        YAML::Node result;
        result["kind"]  = prefix + " expression";
        result["value"] = expression->GetValue();

        Return_.reset();
        Return_ = result;
    }

    void Type_(const std::string& prefix, TType* type) {
        YAML::Node result;
        result["kind"]     = prefix + " type";
        result["is-array"] = type->IsArray();

        Return_.reset();
        Return_ = result;
    }
};

#endif//COMPILER_YAML_VISITOR_HH
