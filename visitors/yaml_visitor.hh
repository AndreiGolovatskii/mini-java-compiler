#ifndef COMPILER_YAML_VISITOR_HH
#define COMPILER_YAML_VISITOR_HH

#include <iostream>

#include "yaml-cpp/yaml.h"

#include "ast_components.hh"
#include "i_visitor.hh"

class TYamlVisitor : public IVisitor {
public:
    void Visit(struct TAndExpression* expression) override {
        ProcessBinaryExpression_("and ", expression);
    }

    void Visit(struct TAssertionStatement* statement) override {
        YAML::Node result;
        result["kind"] = "assert statement";
        statement->Expression()->Accept(this);
        result["expresion"] = Return_;

        SetReturn_(result);
    }

    void Visit(struct TAssignmentStatement* statement) override {
        YAML::Node result;
        result["kind"] = "assignment statement";
        statement->Expression()->Accept(this);
        result["expression"] = Return_;
        statement->Lvalue()->Accept(this);
        result["lvalue"] = Return_;

        SetReturn_(result);
    }

    void Visit(struct TBooleanExpression* expression) override {
        ProcessValueExpression_("boolean", expression);
    }

    void Visit(struct TClassDeclaration* declaration) override {
        YAML::Node result;
        result["kind"] = "class";
        result["name"] = declaration->ClassName();
        declaration->Members().Accept(this);
        result["members"] = Return_;

        SetReturn_(result);
    }

    void Visit(struct TClassMemberDeclarationList* list) override {
        ProcessList_(list);
    }

    void Visit(struct TDivExpression* expression) override {
        ProcessBinaryExpression_("div", expression);
    }

    void Visit(struct TEqExpression* expression) override {
        ProcessBinaryExpression_("eq", expression);
    }

    void Visit(struct TExpressionList* list) override {
        ProcessList_(list);
    }

    void Visit(struct TFieldInvocation* invocation) override {
        YAML::Node result;
        result["kind"]       = "field invocation";
        result["identifier"] = invocation->Identifier();

        SetReturn_(result);
    }

    void Visit(struct TFieldInvocationExpression* expression) override {
        YAML::Node result;
        result["kind"] = "field invocation expression";
        expression->Method()->Accept(this);
        result["invocation"] = Return_;

        SetReturn_(result);
    }

    void Visit(struct TFieldInvocationIndexed* invocationIndexed) override {
        YAML::Node result;
        result["kind"] = "field invocation indexed";
        invocationIndexed->Index()->Accept(this);
        result["index"] = Return_;

        SetReturn_(result);
    }

    void Visit(struct TGeExpression* expression) override {
        ProcessBinaryExpression_("ge", expression);
    }

    void Visit(struct TGeqExpression* expression) override {
        ProcessBinaryExpression_("geq", expression);
    }

    void Visit(struct TIdentifierExpression* expression) override {
        YAML::Node result;
        result["kind"]       = "identifier expression";
        result["identifier"] = expression->Identifier();

        SetReturn_(result);
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

        SetReturn_(result);
    }

    void Visit(struct TIfStatement* statement) override {
        YAML::Node result;
        result["kind"] = "if statement";

        statement->Condition()->Accept(this);
        result["condition"] = Return_;

        statement->Statement()->Accept(this);
        result["statement"] = Return_;

        SetReturn_(result);
    }

    void Visit(struct TIndexExpression* expression) override {
        YAML::Node result;
        result["kind"] = "index expression";

        expression->Expression()->Accept(this);
        result["expression"] = Return_;

        expression->Index()->Accept(this);
        result["index"] = Return_;

        SetReturn_(result);
    }

    void Visit(struct TIntExpression* expression) override {
        ProcessValueExpression_("int", expression);
    }

    void Visit(struct TLeExpression* expression) override {
        ProcessBinaryExpression_("le", expression);
    }

    void Visit(struct TStatementList* list) override {
        ProcessList_(list);
    }

    void Visit(struct TLengthExpression* expression) override {
        YAML::Node result;
        result["kind"] = "length expression";

        SetReturn_(result);
    }

    void Visit(struct TLeqExpression* expression) override {
        ProcessBinaryExpression_("leq", expression);
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

        SetReturn_(result);
    }

    void Visit(struct TMemberVariableDeclaration* declaration) override {
        YAML::Node result;
        result["kind"] = "member variable declaration";
        result["name"] = declaration->Variable().Name();

        declaration->Variable().Type()->Accept(this);
        result["variable-type"] = Return_;

        SetReturn_(result);
    }

    void Visit(struct TMethodInvocation* invocation) override {
        YAML::Node result;
        result["kind"]   = "method invocation";
        result["method"] = invocation->Method();

        invocation->Expression()->Accept(this);
        result["expression"] = Return_;

        invocation->Arguments()->Accept(this);
        result["arguments"] = Return_;

        SetReturn_(result);
    }

    void Visit(struct TMethodInvocationExpression* expression) override {
        YAML::Node result;
        result["kind"] = "method invocation expression";
        expression->Invocation()->Accept(this);
        result["invocation"] = Return_;

        SetReturn_(result);
    }

    void Visit(struct TMethodInvocationStatement* statement) override {
        YAML::Node result;
        result["statement"] = "method invocation statement";

        statement->Method()->Accept(this);
        result["invocation"] = Return_;

        SetReturn_(result);
    }

    void Visit(struct TModExpression* expression) override {
        ProcessBinaryExpression_("mod", expression);
    }

    void Visit(struct TMulExpression* expression) override {
        ProcessBinaryExpression_("mul", expression);
    }

    void Visit(struct TNewArrayExpression* expression) override {
        YAML::Node result;
        result["kind"] = "new array expression";

        expression->Type()->Accept(this);
        result["value-type"] = Return_;

        expression->Size()->Accept(this);
        result["size"] = Return_;

        SetReturn_(result);
    }

    void Visit(struct TNewExpression* expression) override {
        YAML::Node result;
        result["kind"] = "new expression";

        expression->Type()->Accept(this);
        result["value-type"] = Return_;

        SetReturn_(result);
    }

    void Visit(struct TNotExpression* expression) override {
        YAML::Node result;
        result["kind"] = "not expression";

        expression->Expression()->Accept(this);
        result["expression"] = Return_;

        SetReturn_(result);
    }

    void Visit(struct TOrExpression* expression) override {
        ProcessBinaryExpression_("or", expression);
    }

    void Visit(struct TPrintlnStatement* statement) override {
        YAML::Node result;
        result["kind"] = "print statement";

        statement->Expression()->Accept(this);
        result["expression"] = Return_;

        SetReturn_(result);
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

        SetReturn_(result);
    }

    void Visit(struct TClassDeclarationList* list) override {
        ProcessList_(list);
    }

    void Visit(struct TSubExpression* expression) override {
        ProcessBinaryExpression_("sub", expression);
    }

    void Visit(struct TSumExpression* expression) override {
        ProcessBinaryExpression_("sum", expression);
    }

    void Visit(struct TThisExpression* expression) override {
        YAML::Node result;
        result["kind"] = "this expression";

        SetReturn_(result);
    }

    void Visit(struct TVariableDeclarationStatement* statement) override {
        YAML::Node result;
        result["kind"] = "variable declaration statement";

        statement->Variable().Type()->Accept(this);
        result["variable-type"] = Return_;

        result["variable-name"] = statement->Variable().Name();

        SetReturn_(result);
    }

    void Visit(struct TWhileStatement* statement) override {
        YAML::Node result;
        result["kind"] = "while statement";

        statement->Condition()->Accept(this);
        result["condition"] = Return_;

        statement->Statement()->Accept(this);
        result["statement"] = Return_;

        SetReturn_(result);
    }

    void Visit(struct TIntType* type) override {
        ProcessType_("int", type);
    }

    void Visit(struct TBooleanType* type) override {
        ProcessType_("boolean", type);
    }

    void Visit(struct TVoidType* type) override {
        ProcessType_("void", type);
    }

    void Visit(struct TIdentifierType* type) override {
        YAML::Node result;
        result["kind"]       = "identifier type";
        result["identifier"] = type->Identifier();
        result["is-array"]   = type->IsArray();

        SetReturn_(result);
    }

    void Visit(struct TUnaryMinusExpression* expression) override {
        YAML::Node result;
        result["kind"] = "unary minus expression";

        expression->Expression()->Accept(this);
        result["expression"] = Return_;

        SetReturn_(result);
    }

    void Print(std::ostream& out) const {
        out << Root_;
    }

private:
    YAML::Node Root_;
    YAML::Node Return_;

    void SetReturn_(YAML::Node& result) {
        Return_.reset();
        Return_ = result;
    }

    template<typename T>
    void ProcessList_(T* list) {
        YAML::Node result;
        for (const auto& elem : *list) {
            elem->Accept(this);
            result.push_back(Return_);
        }
        SetReturn_(result);
    }

    void ProcessBinaryExpression_(const std::string& prefix, TBinaryExpression* expression) {
        YAML::Node result;
        result["kind"] = prefix + " expression";

        expression->Lhs()->Accept(this);
        result["lhs"] = Return_;

        expression->Rhs()->Accept(this);
        result["rhs"] = Return_;

        SetReturn_(result);
    }

    template<typename T>
    void ProcessValueExpression_(const std::string& prefix, T* expression) {
        YAML::Node result;
        result["kind"]  = prefix + " expression";
        result["value"] = expression->GetValue();

        SetReturn_(result);
    }

    void ProcessType_(const std::string& prefix, TType* type) {
        YAML::Node result;
        result["kind"]     = prefix + " type";
        result["is-array"] = type->IsArray();

        SetReturn_(result);
    }
};

#endif//COMPILER_YAML_VISITOR_HH
