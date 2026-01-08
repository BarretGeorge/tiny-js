#pragma once

#include "object.h"
#include <asmjit/asmjit.h>

using namespace asmjit;

class JitCompiler
{
    JitRuntime rt;

public:
    using JitFn = double (*)(double* args);

    JitFn compile(const Chunk* chunk);

private:
    JitFn compileX86(const Chunk* chunk, CodeHolder& code);

    JitFn compileAArch64(const Chunk* chunk, CodeHolder& code);
};
