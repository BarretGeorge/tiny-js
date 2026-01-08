#include "jit.h"
#include <iostream>
#include <vector>
#include <cstring>

void pushDouble(std::vector<uint8_t>& bc, double val)
{
    uint8_t bytes[8];
    std::memcpy(bytes, &val, 8);
    for (auto b : bytes) bc.push_back(b);
}

int main()
{
    JitCompiler compiler;

    std::vector<uint8_t> bytecode;

   /**
    * 计算 (10 + 20) - 5
    */
    bytecode.push_back(static_cast<uint8_t>(OpCode::OP_CONSTANT));
    pushDouble(bytecode, 10.0);
    bytecode.push_back(static_cast<uint8_t>(OpCode::OP_CONSTANT));
    pushDouble(bytecode, 20.0);
    bytecode.push_back(static_cast<uint8_t>(OpCode::OP_ADD));
    bytecode.push_back(static_cast<uint8_t>(OpCode::OP_CONSTANT));
    pushDouble(bytecode, 5.0);
    bytecode.push_back(static_cast<uint8_t>(OpCode::OP_SUB));
    bytecode.push_back(static_cast<uint8_t>(OpCode::OP_RETURN));

    Chunk chunk;
    chunk.code = bytecode;
    if (const auto func = compiler.compile(&chunk))
    {
        double args[1] = {0.0};
        const double result = func(args);
        // 输出25
        std::cout << "JIT 执行结果: " << result << std::endl;
    }
    else
    {
        std::cout << "JIT 编译失败" << std::endl;
    }
    return 0;
}
