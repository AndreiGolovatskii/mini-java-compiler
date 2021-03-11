%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    class TScanner;
    class TDriver;

    #include "ast_components.hh"
}

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    static yy::parser::symbol_type yylex(TScanner &scanner, TDriver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { TScanner &scanner }
%lex-param { TDriver &driver }
%parse-param { TScanner &scanner }
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

%nterm <bool> static_opt

%nterm <TClassDeclarationList> class_declaration_list
%nterm <TClassDeclarationPtr> class_declaration

%nterm <TStatementListPtr> statement_list
%nterm <TStatementPtr> statement

%nterm <TExpressionPtr> expr

%nterm <TDeclarationListPtr> declaration_list
%nterm <TClassMemberDeclarationPtr> declaration
%nterm <TMemberVariableDeclarationPtr> variable_declaration
%nterm <TMethodDeclarationPtr> method_declaration

%nterm <TVariableList> formals
%nterm <TVariableList> formals_prefix

%nterm <TTypePtr> type
%nterm <TTypePtr> simple_type
%nterm <TTypePtr> array_type
%nterm <TTypePtr> type_identifier

%nterm <TVariableDeclarationStatementPtr> local_variable_declaration

%nterm <std::string> extends

%nterm <TMethodInvocationPtr> method_invocation
%nterm <TFieldInvocationPtr> field_invocation
%nterm <TExpressionListPtr> expr_comma_separated_list
%nterm <TExpressionListPtr> expr_comma_separated_list_prefix

%%
%start program;

program:
    class_declaration_list {
        driver.Program_ = std::make_unique<TProgram>(std::move($1));
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
    | class_declaration_list class_declaration {
        $$ = std::move($1);
        $$.emplace_back(std::move($2));
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
        $$ = std::make_unique<TClassMemberDeclarationList>();
    }
    | declaration_list declaration {
        $$ = std::move($1);
        $$->emplace_back(std::move($2));
    }


declaration:
    variable_declaration {
        $$ = std::move($1);
    }
    | method_declaration {
        $$ = std::move($1);
    }


method_declaration:
    "public" static_opt type IDENTIFIER "(" formals ")" "{" statement_list "}" {
        $$ = std::make_unique<TMemberMethodDeclaration>(std::move($3),
                                                  TMethodSignature(std::move($4), std::move($6)),
                                                  std::move($9));
        if ($2) {
            $$->MakeStatic();
        }
    }


static_opt:
    %empty {$$ = false;}
    | "static" {$$ = true;}


variable_declaration:
    type IDENTIFIER ";" {
        $$ = std::make_unique<TMemberVariableDeclaration>(TVariable(std::move($1), std::move($2)));
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

%nonassoc NO_ELSE;
%nonassoc "else";


%right "||";
%right "&&";
%precedence "!";
%left ">" "<" "<=" ">=" "==";
%left "+" "-";
%left "*" "/" "%";
%left UMINUS;
%nonassoc NO_BRACKET;
%nonassoc "[";
%nonassoc ".";

statement:
    "assert" "(" expr ")" ";" {$$ = std::make_unique<TAssertionStatement>(std::move($3));}
    | local_variable_declaration {$$ = std::move($1);}
    | "{" statement_list "}" {$$ = std::move($2);}
    | "if"  "(" expr ")" statement %prec NO_ELSE {$$ = std::make_unique<TIfStatement>(std::move($3), std::move($5));}
    | "if"  "(" expr ")" statement "else" statement {
        $$ = std::make_unique<TIfElseStatement>(std::move($3), std::move($5), std::move($7));
    }
    | "while"  "(" expr ")" statement {$$ = std::make_unique<TWhileStatement>(std::move($3), std::move($5));}
    | "System.out.println" "(" expr ")" ";" {$$ = std::make_unique<TPrintlnStatement>(std::move($3));}
    | expr "=" expr ";"  {$$ = std::make_unique<TAssignmentStatement>(std::move($1), std::move($3));}
    | "return" expr ";" {$$ = std::make_unique<TReturnStatement>(std::move($2));}
    | method_invocation ";" {$$ = std::make_unique<TMethodInvocationStatement>(std::move($1));}


local_variable_declaration:
    type IDENTIFIER ";" {
        $$ = std::make_unique<TVariableDeclarationStatement>(TVariable(std::move($1), std::move($2)));
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
    expr "." IDENTIFIER %prec NO_BRACKET {
        $$ = std::make_unique<TFieldInvocation>(std::move($3));
    }
    | expr "." IDENTIFIER "[" expr "]" {
        $$ = std::make_unique<TFieldInvocationIndexed>(std::move($3), std::move($5));
    }


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
    | "-" expr %prec UMINUS {$$ = std::make_unique<TUnaryMinusExpression>(std::move($2));}

    | expr "[" expr "]"  {$$ = std::make_unique<TIndexExpression>(std::move($1), std::move($3));}
    | expr "."  "length" {$$ = std::make_unique<TLengthExpression>(std::move($1));}
    | "new" simple_type "[" expr "]" {$$ = std::make_unique<TNewArrayExpression>(std::move($2), std::move($4));}
    | "new" type_identifier "(" ")" {$$ = std::make_unique<TNewExpression>(std::move($2));}
    | "!" expr {$$ = std::make_unique<TNotExpression>(std::move($2));}
    | "(" expr ")" {$$ = std::move($2);}
    | IDENTIFIER {$$ = std::make_unique<TIdentifierExpression>(std::move($1));}
    | INTEGRAL_LITERAL {$$ = std::make_unique<TIntExpression>($1);}
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
