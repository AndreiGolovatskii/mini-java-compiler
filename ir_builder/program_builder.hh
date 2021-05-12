#pragma once

#include "partial_visitor.hh"

#include "base_builder.hh"
#include "class_declaration_builder.hh"
#include "class_realization_builder.hh"
#include "function_declaration_builder.hh"
#include "function_realization_builder.hh"

class TProgramBuilder : public TBaseBuilder {
public:
    explicit TProgramBuilder(TBaseBuilder& base): TBaseBuilder(base) {}

    template<class ...Args>
    explicit TProgramBuilder(Args&&... args): TBaseBuilder(std::forward<Args>(args)...) {}

private:
    void Visit(struct TProgram* program) override {
        TClassesDeclarationBuilder{*this}.Visit(program);
        TClassesRealizationBuilder{*this}.Visit(program);
        TFunctionsDeclarationBuilder{*this}.Visit(program);
        TFunctionsRealizationBuilder{*this}.Visit(program);
    }
};