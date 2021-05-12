#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "class_specification.hh"

template<typename T = std::unique_ptr<TClassSpecification>>
class TSymbolTable {
public:
    TSymbolTable()                    = default;
    TSymbolTable(const TSymbolTable&) = delete;
    TSymbolTable& operator=(const TSymbolTable&) = delete;

    TSymbolTable(TSymbolTable&&) noexcept = default;
    TSymbolTable& operator=(TSymbolTable&&) noexcept = default;

    [[nodiscard]] T& Get(const std::string& name) {
        if (Content_.contains(name)) {
            return Content_.at(name);
        }
        throw std::logic_error{"Compilation error: Undefined symbol"};// TODO Compilation Error
    }

    [[nodiscard]] bool Has(const std::string& name) {
        return Content_.contains(name);
    }

    template<class... Args>
    void Add(const std::string& name, Args&&... args) {
        if (Content_.contains(name)) {
            throw std::logic_error{"Compilation error: Symbol redefinition"};// TODO Compilation Error
        }
        Content_.emplace(std::pair<const std::string, T>(name, T{std::forward<Args>(args)...}));
    }


private:
    std::unordered_map<std::string, T> Content_;
};