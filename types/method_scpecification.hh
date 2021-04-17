#pragma once

#include <memory>

#include "i_type.hh"


class TArgument {
public:
    TArgument(std::string name, std::unique_ptr<IType>&& type) : Name_(std::move(name)), Type_(std::move(type)) {}

    [[nodiscard]] IType* Type() const {
        return Type_.get();
    }

    [[nodiscard]] const std::string& Name() const {
        return Name_;
    }

private:
    std::string Name_;
    std::unique_ptr<IType> Type_;
};


class TMethodSpecification {
public:
    explicit TMethodSpecification(std::unique_ptr<IType>&& returnType, std::vector<TArgument>&& args,
                                  bool isStatic = false)
        : ReturnType_(std::move(returnType)), Args_(std::move(args)), IsStatic_(isStatic) {}

    [[nodiscard]] bool IsStatic() const {
        return IsStatic_;
    }

    [[nodiscard]] IType* ReturnType() const {
        return ReturnType_.get();
    }

    [[nodiscard]] const std::vector<TArgument>& Args() const {
        return Args_;
    }

private:
    std::unique_ptr<IType> ReturnType_;
    std::vector<TArgument> Args_;
    bool IsStatic_;
};
