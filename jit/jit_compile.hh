#pragma once

#include <filesystem>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include "driver.hh"
#include "jit_run.hh"
#include "program_builder.hh"


inline std::pair<std::unique_ptr<llvm::Module>, std::unique_ptr<llvm::LLVMContext>>
JitCompile(const std::filesystem::path& path) {
    TDriver driver;

    if (driver.parse(path) != 0) {
        throw std::logic_error{"parse fail"};
    }

    auto context = std::make_unique<llvm::LLVMContext>();
    auto module  = std::make_unique<llvm::Module>("main", *context);

    TProgramBuilder builder{*context, *module};
    driver.Program_->Accept(&builder);

    return {std::move(module), std::move(context)};
}

inline llvm::Function* GetEntry(llvm::Module* module) {
    std::optional<llvm::Function*> entry;
    for (auto& func : module->getFunctionList()) {
        if (func.hasName() && func.getName().endswith("#main")) {
            if (entry.has_value()) {
                throw std::logic_error{"Multiple main functions"};
            }
            entry.emplace(&func);
        }
    }

    if (!entry.has_value()) {
        throw std::logic_error{"No main function to entry"};
    }
    return entry.value();
}

inline void JitCompileAndRun(const std::filesystem::path& path) {
    auto [module, context] = JitCompile(path);
    auto entry             = GetEntry(module.get());
    JitRun(std::move(module), entry);
}

inline Status JitCompileAndRunInSubprocess(const std::filesystem::path& path, int timeout = 1) {
    auto [module, context] = JitCompile(path);
    auto entry             = GetEntry(module.get());
    return JitRunSubprocess(std::move(module), entry, timeout);
}