#ifndef TINY_JS_BASE_H
#define TINY_JS_BASE_H

#include "vm.h"

Value nativePrint(VM& vm, int argc, const Value* args);

Value nativeNow(VM& vm, int argc, const Value* args);

#endif //TINY_JS_BASE_H
