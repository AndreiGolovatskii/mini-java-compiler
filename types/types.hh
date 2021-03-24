#pragma once

#include <unordered_map>

#include "ast_components.hh"
#include "class_specification.hh"
#include "i_type.hh"

class TIntegerType : public IType {
public:
    size_t Size() override {
        return sizeof(int);
    }
};

class TClassPtrType : public IType {
public:
    size_t Size() override {
        return sizeof(void*);
    }

    explicit TClassPtrType(TClassSpecification* spec) : Spec_(spec) {}

private:
    TClassSpecification* Spec_;
};

class TArrayType : public IType {
public:
    size_t Size() override {
        return sizeof(void*);
    }
};

class TBooleanType : public IType {
public:
    size_t Size() override {
        return sizeof(bool);
    }
};

class TVoidType : public IType {
public:
    size_t Size() override {
        return 0;
    }
};