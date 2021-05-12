#ifndef COMPILER_I_VISITOR_HH
#define COMPILER_I_VISITOR_HH

#include "ast_forward_declaration.hh"

class IVisitor {
public:
    virtual void Visit(class TAndExpression*)                = 0;
    virtual void Visit(class TAssertionStatement*)           = 0;
    virtual void Visit(class TAssignmentStatement*)          = 0;
    virtual void Visit(class TBooleanExpression*)            = 0;
    virtual void Visit(class TClassDeclaration*)             = 0;
    virtual void Visit(class TClassMemberDeclarationList*)   = 0;
    virtual void Visit(class TDivExpression*)                = 0;
    virtual void Visit(class TEqExpression*)                 = 0;
    virtual void Visit(class TNEqExpression*)                = 0;
    virtual void Visit(class TExpressionList*)               = 0;
    virtual void Visit(class TFieldInvocation*)              = 0;
    virtual void Visit(class TFieldInvocationExpression*)    = 0;
    virtual void Visit(class TGeExpression*)                 = 0;
    virtual void Visit(class TGeqExpression*)                = 0;
    virtual void Visit(class TIdentifierExpression*)         = 0;
    virtual void Visit(class TIfElseStatement*)              = 0;
    virtual void Visit(class TIfStatement*)                  = 0;
    virtual void Visit(class TIndexExpression*)              = 0;
    virtual void Visit(class TIntExpression*)                = 0;
    virtual void Visit(class TLeExpression*)                 = 0;
    virtual void Visit(class TLengthExpression*)             = 0;
    virtual void Visit(class TLeqExpression*)                = 0;
    virtual void Visit(class TMemberMethodDeclaration*)      = 0;
    virtual void Visit(class TMemberVariableDeclaration*)    = 0;
    virtual void Visit(class TMethodInvocation*)             = 0;
    virtual void Visit(class TMethodInvocationExpression*)   = 0;
    virtual void Visit(class TMethodInvocationStatement*)    = 0;
    virtual void Visit(class TModExpression*)                = 0;
    virtual void Visit(class TMulExpression*)                = 0;
    virtual void Visit(class TNewArrayExpression*)           = 0;
    virtual void Visit(class TNewExpression*)                = 0;
    virtual void Visit(class TNotExpression*)                = 0;
    virtual void Visit(class TOrExpression*)                 = 0;
    virtual void Visit(class TPrintlnStatement*)             = 0;
    virtual void Visit(class TProgram*)                      = 0;
    virtual void Visit(class TReturnStatement*)              = 0;
    virtual void Visit(class TStatementList*)                = 0;
    virtual void Visit(class TSubExpression*)                = 0;
    virtual void Visit(class TSumExpression*)                = 0;
    virtual void Visit(class TThisExpression*)               = 0;
    virtual void Visit(class TVariableDeclarationStatement*) = 0;
    virtual void Visit(class TWhileStatement*)               = 0;
    virtual void Visit(class TClassDeclarationList*)         = 0;
    virtual void Visit(class TIntTypeNode*)                  = 0;
    virtual void Visit(class TBooleanTypeNode*)              = 0;
    virtual void Visit(class TVoidTypeNode*)                 = 0;
    virtual void Visit(class TIdentifierTypeNode*)           = 0;
    virtual void Visit(class TArrayTypeNode*)                = 0;
    virtual void Visit(class TUnaryMinusExpression*)         = 0;

    virtual ~IVisitor() = default;
};

#endif//COMPILER_I_VISITOR_HH
