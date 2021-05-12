#pragma once

#include <deque>
#include <string>
#include <utility>

#include "ast_components.hh"
#include "i_type.hh"
#include "scope.hh"

template<class T = std::unique_ptr<TVariableSpecification>>
class TScopeTable {
public:
    TScopeTable() = default;

    TScopeTable(const TScopeTable<T>& other) = delete;
    TScopeTable(TScopeTable<T>&& other)      = delete;


    TScopeTable<T> operator=(const TScopeTable<T>& other) = delete;
    TScopeTable<T> operator=(TScopeTable<T>&& other) = delete;


    void BeginScope(const std::string& name = "") {
        AllScopes_.emplace_back(name, Current_);
        Current_ = &AllScopes_.back();
    }

    void EndScope() {
        Current_ = Current_->Parent();
    }

    template<class... Args>
    void AddVariable(const std::string& name, Args&&... args) {
        Current_->AddVariable(name, std::forward<Args>(args)...);
    }

    [[nodiscard]] bool HasVariable(const std::string& name) const {
        auto* findIn = Current_;
        while (findIn) {
            if (findIn->HasVariable(name)) {
                return true;
            }
            findIn = findIn->Parent();
        }
        return false;
    }

    [[nodiscard]] const T& Variable(const std::string& name) const {
        auto* findIn = Current_;
        while (findIn) {
            if (findIn->HasVariable(name)) {
                return findIn->Variable(name);
            }
            findIn = findIn->Parent();
        }
        throw std::logic_error{"Compilation Error: Undeclared identifier " + name};// TODO Compilation Error
    }

private:
    TScopeTreeNode<T>* Current_{nullptr};
    std::deque<TScopeTreeNode<T>> AllScopes_;
};
