#include "native/base.h"
#include <iostream>

Value nativeNow(VM& vm, int argc, const Value* args)
{
    const auto now = std::chrono::system_clock::now().time_since_epoch();
    return static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(now).count()) / 1000.0;
}

Value nativePrint(VM& vm, const int argc, const Value* args)
{
    for (int i = 0; i < argc; i++) std::cout << valToString(args[i]) << (i < argc - 1 ? " " : "");
    std::cout << std::endl;
    return std::monostate{};
}
