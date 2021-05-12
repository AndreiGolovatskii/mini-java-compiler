#pragma once

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/TargetSelect.h>
#include <sys/types.h>
#include <unistd.h>

#include "llvm/IR/Module.h"

class Status {
public:
    static Status Ok() {
        return Status(true);
    }

    static Status Fail() {
        return Status(false);
    }

    [[nodiscard]] bool IsOk() const {
        return status_;
    }

    bool operator==(const Status& other) const {
        return status_ == other.status_;
    }

private:
    explicit Status(bool res) : status_(res) {}

    bool status_;
};

void JitRun(std::unique_ptr<llvm::Module> module, llvm::Function* entry) {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    std::string errStr;
    auto* EE =
            llvm::EngineBuilder(std::move(module)).setErrorStr(&errStr).setEngineKind(llvm::EngineKind::JIT).create();

    if (!EE) {
        throw std::logic_error{"Engine build failed: " + errStr};
    }

    llvm::GenericValue GV = EE->runFunction(entry, {});
}

Status JitRunSubprocess(std::unique_ptr<llvm::Module> module, llvm::Function* entry, int timeout = 1) {
    pid_t childPid = fork();
    if (!childPid) {
        alarm(timeout);
        JitRun(std::move(module), entry);
        exit(0);
    }

    int status;
    waitpid(childPid, &status, 0);

    return (WIFEXITED(status) != 0 && (WEXITSTATUS(status) == 0)) ? Status::Ok() : Status::Fail();
}
