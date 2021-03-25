#pragma once

#include <memory>

#include "i_type.hh"

class TVariableSpecification {
public:
    TVariableSpecification(std::unique_ptr<IType>&& type, bool isStatic) : Type_(std::move(type)), IsStatic_(isStatic) {
        assert(isStatic == false);// TODO Support static variable
    }

    [[nodiscard]] IType* Type() const {
        return Type_.get();
    }

    [[nodiscard]] bool IsStatic() const {
        return IsStatic_;
    }

private:
    std::unique_ptr<IType> Type_;
    bool IsStatic_;
};