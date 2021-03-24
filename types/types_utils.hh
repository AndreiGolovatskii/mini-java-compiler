#pragma once

#include "class_specification.hh"
#include "types.hh"


TClassSpecification* ClassTypeSpec(IType* type) {
    auto* ptr = dynamic_cast<TClassPtrType*>(type);
    if (ptr) {
        return ptr->Spec();
    }
    return nullptr;
}

bool IsEqual(IType* lhs, IType* rhs) {
    return typeid(lhs) == typeid(rhs);
}