#pragma once

#include <deque>
#include <string>

#include "ast_components.hh"
#include "i_type.hh"
#include "scope.hh"

class TScopeTable {
public:
    void BeginScope(const std::string& name = "") {
        AllScopes_.emplace_back(name, Current_);
        Current_ = &AllScopes_.back();
    }

    void EndScope() {
        Current_ = Current_->Parent();
    }

    void AddVariable(const std::string& name, std::unique_ptr<IType>&& type) {
        Current_->AddVariable(name, std::move(type));
    }

    [[nodiscard]] TVariableSpecification* Variable(const std::string& name) const {
        TScopeTreeNode* findIn = Current_;
        while (findIn) {
            auto* variable = findIn->TryVariable(name);
            if (variable) {
                return variable;
            }
            findIn = findIn->Parent();
        }
        throw std::logic_error{"Compilation Error: Undeclared identifier " + name};// TODO Compilation Error
    }

private:
    TScopeTreeNode* Current_{nullptr};
    std::deque<TScopeTreeNode> AllScopes_;
};
