%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    class Scanner;
    class TDriver;

    #include "class_declaration.hh"
    #include "declaration.hh"
    #include "expression.hh"
    #include "invocation.hh"
    #include "lvalue.hh"
    #include "method_declaration.hh"
    #include "program.hh"
    #include "statement.hh"
    #include "type.hh"
    #include "variable_declaration.hh"
}

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    static yy::parser::symbol_type yylex(Scanner &scanner, TDriver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { TDriver &driver }
%parse-param { Scanner &scanner }
%parse-param { TDriver &driver }

%locations

%define api.token.prefix {TOK_}

%token
    EOF 0 "end of file"

    NEWLINE "newline"

    ASSIGN "="
    MINUS "-"
    PLUS "+"
    SLASH "/"
    STAR "*"
    PERCENT "%"
    GT ">"
    LT "<"
    GE "=>"
    LE "<="
    EQ "=="

    NOT "!"
    AND "&&"
    OR "||"

    LPAREN "("
    RPAREN ")"
    LBRACKET "["
    RBRACKET "]"
    DOUBLEBRACKET "[]"
    LEFTSCOPE "{"
    RIGHTSCOPE "}"
    DOUBLE_COLON "::"
    QUOTE "'"
    DOUBLE_QUOTE "\""
    COMMA ","
    SEMICOLON ";"

    PRINT "System.out.println"
    MAIN "main"
    IF "if"
    ELSE "else"
    WHILE "while"
    RETURN "return"
    ASSERT "assert"
    EXTENDS "extends"
    NEW "new"
    DOT "."

    CLASS "class"
    PUBLIC "public"
    STATIC "static"

    INT "int"
    BOOLEAN "boolean"
    VOID "void"

    TRUE "true"
    FALSE "false"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> INTEGRAL_LITERAL "integral_literal"


%nterm <TClassDeclarationPtr> main_class

%nterm <TClassDeclarationList> class_declaration_list
%nterm <TClassDeclarationPtr> class_declaration

%nterm <TStatementListPtr> statement_list
%nterm <TStatementPtr> statement

%nterm <TExpressionPtr> expr

%nterm <TDeclarationListPtr> declaration_list
%nterm <TDeclarationPtr> declaration
%nterm <TVariableDeclarationPtr> variable_declaration
%nterm <TMethodDeclarationPtr> method_declaration

%nterm <TVariableList> formals
%nterm <TVariableList> formals_prefix

%nterm <TTypePtr> type
%nterm <TTypePtr> simple_type
%nterm <TTypePtr> array_type
%nterm <TTypePtr> type_identifier

%nterm <TVariableDeclarationStatementPtr> local_variable_declaration

%nterm <TLvaluePtr> lvalue

%nterm <std::string> extends

%nterm <TMethodInvocationPtr> method_invocation
%nterm <TFieldInvocationPtr> field_invocation
%nterm <TExpressionListPtr> expr_comma_separated_list
%nterm <TExpressionListPtr> expr_comma_separated_list_prefix

%%
%start program;

program:
    main_class class_declaration_list {
        driver.Program_ = std::make_unique<TProgram>(std::move($1), std::move($2));
    }


main_class:
    "class" IDENTIFIER "{" PUBLIC STATIC "void" "main" "(" ")" "{" statement_list "}" "}" {
        $$ = std::make_unique<TClassDeclaration>(std::move($2));
        TMethodDeclarationPtr main = std::make_unique<TMethodDeclaration>(std::make_unique<TVoidType>(),
                                                                          TMethodSignature{"main", TVariableList{}},
                                                                          std::move($11));
        main->MakeStatic();
        $$->AddMethod(std::move(main));
    }


statement_list:
    %empty {
        $$ = std::make_unique<TStatementList>();
    }
    | statement_list statement {
        $$ = std::move($1);
        $$->emplace_back(std::move($2));
    }


class_declaration_list:
    %empty {
        $$ = TClassDeclarationList();
    }
    | class_declaration class_declaration_list {
        $$ = std::move($2);
        $$.emplace_back(std::move($1));
    }


class_declaration:
    "class" IDENTIFIER extends "{" declaration_list "}" {
        $$ = std::make_unique<TClassDeclaration>(std::move($2), std::move($3));
        $$->AddMethods(std::move($5));
    }


extends:
    %empty {
        $$ = "object";
    }
    | "extends" IDENTIFIER {
        $$ = std::move($2);
    }


declaration_list:
    %empty {
        $$ = std::make_unique<TDeclarationList>();
    }
    | declaration declaration_list {
        $$ = std::move($2);
        $$->emplace_back(std::move($1));
    }


declaration:
    variable_declaration {
        $$ = std::move($1);
    }
    | method_declaration {
        $$ = std::move($1);
    }

method_declaration:
    "public" type IDENTIFIER "(" formals ")" "{" statement_list "}" {
        $$ = std::make_unique<TMethodDeclaration>(std::move($2),
                                                  TMethodSignature(std::move($3), std::move($5)),
                                                  std::move($8));
    }


variable_declaration:
    type IDENTIFIER ";" {
        $$ = std::make_unique<TVariableDeclaration>(TVariable(std::move($1), std::move($2)));
    }


formals:
    %empty {}
    | formals_prefix type IDENTIFIER {
        $$ = std::move($1);
        $$.emplace_back(std::move(TVariable(std::move($2), std::move($3))));
    }


formals_prefix:
    %empty {}
    | formals_prefix type IDENTIFIER "," {
        $$ = std::move($1);
        $$.emplace_back(std::move($2), std::move($3));
    }


type:
    simple_type {$$ = std::move($1);}
    | array_type {$$ = std::move($1);}


simple_type:
    "int" {$$ = std::make_unique<TIntType>();}
    | "boolean" {$$ = std::make_unique<TBooleanType>();}
    | "void" {$$ = std::make_unique<TVoidType>();}
    | type_identifier {$$ = std::move($1);}


array_type:
	simple_type "[]" {
	    $$ = std::move($1);
	    $$->MakeArray();
	}


type_identifier:
    IDENTIFIER {
        $$ = std::make_unique<TIdentifierType>(std::move($1));
    }


statement:
    "assert" "(" expr ")" ";" {$$ = std::make_unique<TAssertionStatement>(std::move($3));}
    | local_variable_declaration {$$ = std::move($1);}
    | "{" statement_list "}" {$$ = std::move($2);}
    | "if"  "(" expr ")" statement {$$ = std::make_unique<TIfStatement>(std::move($3), std::move($5));}
    | "if"  "(" expr ")" statement "else" statement {
        $$ = std::make_unique<TIfElseStatement>(std::move($3), std::move($5), std::move($7));
    }
    | "while"  "(" expr ")" statement {$$ = std::make_unique<TWhileStatement>(std::move($3), std::move($5));}
    | "System.out.println" "(" expr ")" ";" {$$ = std::make_unique<TPrintlnStatement>(std::move($3));}
    | lvalue "=" expr ";"  {$$ = std::make_unique<TAssignmentStatement>(std::move($1), std::move($3));}
    | "return" expr ";" {$$ = std::make_unique<TReturnStatement>(std::move($2));}
    | method_invocation ";" {$$ = std::make_unique<TMethodInvocationStatement>(std::move($1));}


local_variable_declaration:
    variable_declaration {
        $$ = std::make_unique<TVariableDeclarationStatement>(std::move($1));
    }


method_invocation:
    expr "." IDENTIFIER "(" expr_comma_separated_list ")" {
        $$ = std::make_unique<TMethodInvocation>(std::move($1), std::move($3), std::move($5));
    }


expr_comma_separated_list:
    %empty {
        $$ = std::make_unique<TExpressionList>();
    }
    | expr_comma_separated_list_prefix expr {
        $$ = std::move($1);
        $$->emplace_back(std::move($2));
    }


expr_comma_separated_list_prefix:
    %empty {
        $$ = std::make_unique<TExpressionList>();
    }
    | expr_comma_separated_list_prefix expr "," {
        $$ = std::move($1);
        $$->push_back(std::move($2));
    }


field_invocation:
    "this" "." IDENTIFIER {
        $$ = std::make_unique<TFieldInvocation>(std::move($3));
    }
    | "this" "." IDENTIFIER "[" expr "]" {
        $$ = std::make_unique<TFieldInvocationIndexed>(std::move($3), std::move($5));
    }


lvalue:
    IDENTIFIER {
        $$ = std::make_unique<TLvalueIdentifier>(std::move($1));
    }
    | IDENTIFIER "[" expr "]" {
        $$ = std::make_unique<TLvalueIdentifierIndexed>(std::move($1), std::move($3));
    }
    | field_invocation {
        $$ = std::make_unique<TLvalueFieldInvocation>(std::move($1));
    }


%right "||";
%right "&&";
%precedence "!";
%left ">" "<" "<=" ">=" "==";
%left "+" "-";
%left "*" "/" "%";


expr:
    expr "&&" expr {$$ = std::make_unique<TAndExpression>(std::move($1), std::move($3));}
    | expr "||" expr {$$ = std::make_unique<TOrExpression>(std::move($1), std::move($3));}

    | expr "<" expr {$$ = std::make_unique<TLeExpression>(std::move($1), std::move($3));}
    | expr ">" expr {$$ = std::make_unique<TGeExpression>(std::move($1), std::move($3));}
    | expr ">=" expr {$$ = std::make_unique<TGeqExpression>(std::move($1), std::move($3));}
    | expr "<=" expr {$$ = std::make_unique<TLeqExpression>(std::move($1), std::move($3));}
    | expr "==" expr {$$ = std::make_unique<TEqExpression>(std::move($1), std::move($3));}

    | expr "+" expr {$$ = std::make_unique<TSumExpression>(std::move($1), std::move($3));}
    | expr "-" expr {$$ = std::make_unique<TSubExpression>(std::move($1), std::move($3));}
    | expr "*" expr {$$ = std::make_unique<TMulExpression>(std::move($1), std::move($3));}
    | expr "/" expr {$$ = std::make_unique<TDivExpression>(std::move($1), std::move($3));}
    | expr "%" expr {$$ = std::make_unique<TModExpression>(std::move($1), std::move($3));}

    | expr "[" expr "]"  {$$ = std::make_unique<TIndexExpression>(std::move($1), std::move($3));}
    | expr "." "length" {$$ = std::make_unique<TLengthExpression>(std::move($1));}
    | "new" simple_type "[" expr "]" {$$ = std::make_unique<TNewArrayExpression>(std::move($2), std::move($4));}
    | "new" type_identifier "(" ")" {$$ = std::make_unique<TNewExpression>(std::move($2));}
    | "!" expr {$$ = std::make_unique<TNotExpression>(std::move($2));}
    | "(" expr ")" {$$ = std::move($2);}
    | IDENTIFIER {$$ = std::make_unique<TIdentifierExpression>(std::move($1));}
    | INTEGRAL_LITERAL {$$ = std::make_unique<TIntExpression>($1);}
    | "-" INTEGRAL_LITERAL {$$ = std::make_unique<TIntExpression>(-$2);}
    | "this" {$$ = std::make_unique<TThisExpression>();}
    | "true" {$$ = std::make_unique<TBooleanExpression>(true);}
    | "false" {$$ = std::make_unique<TBooleanExpression>(false);}
    | method_invocation {$$ = std::make_unique<TMethodInvocationExpression>(std::move($1));}
    | field_invocation {$$ = std::make_unique<TFieldInvocationExpression>(std::move($1));}

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
