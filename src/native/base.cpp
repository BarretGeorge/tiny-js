#include "native/base.h"
#include <iostream>
#include <chrono>
#include <thread>

uint64_t getNowMillis()
{
    const auto now = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
}

uint64_t getNowMicros()
{
    const auto now = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::microseconds>(now).count();
}

Value nativeNow(VM& vm, int argc, const Value* args)
{
    return static_cast<double>(getNowMillis());
}

Value nativePrint(VM& vm, const int argc, const Value* args)
{
    for (int i = 0; i < argc; i++) std::cout << valToString(args[i]) << (i < argc - 1 ? " " : "");
    return std::monostate{};
}

Value nativePrintln(VM& vm, const int argc, const Value* args)
{
    for (int i = 0; i < argc; i++) std::cout << valToString(args[i]) << (i < argc - 1 ? " " : "") << std::endl;
    return std::monostate{};
}

Value nativeStringLength(VM& vm, int argc, const Value* args)
{
    const Value receiver = args[-1];
    const auto* str = dynamic_cast<ObjString*>(std::get<Obj*>(receiver));
    return static_cast<double>(str->chars.size());
}

Value nativeListLength(VM& vm, int argc, const Value* args)
{
    const Value receiver = args[-1];
    const auto* list = dynamic_cast<ObjList*>(std::get<Obj*>(receiver));
    return static_cast<double>(list->elements.size());
}

Value nativeListClear(VM& vm, int argc, const Value* args)
{
    const Value receiver = args[-1];
    auto* list = dynamic_cast<ObjList*>(std::get<Obj*>(receiver));
    list->elements.clear();
    return std::monostate{};
}

Value nativeListPush(VM& vm, const int argc, const Value* args)
{
    const Value receiver = args[-1];
    auto* list = dynamic_cast<ObjList*>(std::get<Obj*>(receiver));
    for (int i = 0; i < argc; i++)
    {
        list->elements.push_back(args[i]);
    }
    return std::monostate{};
}

Value nativeListPop(VM& vm, int argc, const Value* args)
{
    const Value receiver = args[-1];
    auto* list = dynamic_cast<ObjList*>(std::get<Obj*>(receiver));
    if (list->elements.empty())
    {
        throw std::runtime_error("Cannot pop from an empty list.");
    }
    Value val = list->elements.back();
    list->elements.pop_back();
    return val;
}

Value nativeListJoin(VM& vm, const int argc, const Value* args)
{
    const Value receiver = args[-1];
    const auto* list = dynamic_cast<ObjList*>(std::get<Obj*>(receiver));

    std::string sep = ",";
    if (argc > 0 && std::holds_alternative<Obj*>(args[0]))
    {
        if (const auto o = std::get<Obj*>(args[0]); o->type == ObjType::STRING)
        {
            sep = dynamic_cast<ObjString*>(o)->chars;
        }
    }

    std::string res;
    for (size_t i = 0; i < list->elements.size(); i++)
    {
        res += valToString(list->elements[i]);
        if (i < list->elements.size() - 1) res += sep;
    }
    return Value{new ObjString(res)};
}

Value nativeListAt(VM& vm, int argc, const Value* args)
{
    const Value receiver = args[-1];
    const auto* list = dynamic_cast<ObjList*>(std::get<Obj*>(receiver));
    if (argc < 1 || !std::holds_alternative<double>(args[0]))
    {
        throw std::runtime_error("Index must be a number.");
    }
    const int index = static_cast<int>(std::get<double>(args[0]));
    if (index < 0 || index >= list->elements.size())
    {
        throw std::runtime_error("List index out of bounds.");
    }
    return list->elements[index];
}

Value nativeStringAt(VM& vm, const int argc, const Value* args)
{
    const Value receiver = args[-1];
    const auto* str = dynamic_cast<ObjString*>(std::get<Obj*>(receiver));
    if (argc < 1 || !std::holds_alternative<double>(args[0]))
    {
        throw std::runtime_error("Index must be a number.");
    }
    const int index = static_cast<int>(std::get<double>(args[0]));
    if (index < 0 || index >= str->chars.size())
    {
        throw std::runtime_error("String index out of bounds.");
    }
    return Value{new ObjString(std::string(1, str->chars[index]))};
}

Value nativeStringIndexOf(VM& vm, int argc, const Value* args)
{
    const Value receiver = args[-1];
    const auto* str = dynamic_cast<ObjString*>(std::get<Obj*>(receiver));
    if (argc < 1 || !std::holds_alternative<Obj*>(args[0]) ||
        dynamic_cast<ObjString*>(std::get<Obj*>(args[0])) == nullptr)
    {
        throw std::runtime_error("Argument must be a string.");
    }
    const auto* substr = dynamic_cast<ObjString*>(std::get<Obj*>(args[0]));
    const size_t pos = str->chars.find(substr->chars);
    if (pos == std::string::npos)
    {
        return -1.0;
    }
    return static_cast<double>(pos);
}

Value nativeStringSubstring(VM& vm, int argc, const Value* args)
{
    const Value receiver = args[-1];
    const auto* str = dynamic_cast<ObjString*>(std::get<Obj*>(receiver));
    if (argc < 2 || !std::holds_alternative<double>(args[0]) || !std::holds_alternative<double>(args[1]))
    {
        throw std::runtime_error("Arguments must be numbers.");
    }
    const int start = static_cast<int>(std::get<double>(args[0]));
    const int end = static_cast<int>(std::get<double>(args[1]));
    if (start < 0 || end > str->chars.size() || start > end)
    {
        throw std::runtime_error("Invalid substring indices.");
    }
    return Value{new ObjString(str->chars.substr(start, end - start))};
}

Value nativeStringToUpper(VM& vm, int argc, const Value* args)
{
    const Value receiver = args[-1];
    const auto* str = dynamic_cast<ObjString*>(std::get<Obj*>(receiver));
    std::string upperStr = str->chars;
    std::transform(
        upperStr.begin(),
        upperStr.end(),
        upperStr.begin(),
        [](const unsigned char c)
        {
            return std::tolower(c);
        }
    );
    return Value{new ObjString(upperStr)};
}

Value nativeStringToLower(VM& vm, int argc, const Value* args)
{
    const Value receiver = args[-1];
    const auto* str = dynamic_cast<ObjString*>(std::get<Obj*>(receiver));
    std::string lowerStr = str->chars;
    std::transform(
        lowerStr.begin(),
        lowerStr.end(),
        lowerStr.begin(),
        [](const unsigned char c)
        {
            return std::tolower(c);
        }
    );
    return Value{new ObjString(lowerStr)};
}

Value nativeStringTrim(VM& vm, int argc, const Value* args)
{
    const Value receiver = args[-1];
    const auto* str = dynamic_cast<ObjString*>(std::get<Obj*>(receiver));
    const std::string& s = str->chars;

    const size_t start = s.find_first_not_of(" \t\n\r");
    if (start == std::string::npos)
    {
        return vm.newString("");
    }
    const size_t end = s.find_last_not_of(" \t\n\r");
    return vm.newString(s.substr(start, end - start + 1));
}

Value nativeSleep(VM& vm, const int argc, const Value* args)
{
    if (argc < 1 || !std::holds_alternative<double>(args[0]))
    {
        throw std::runtime_error("Sleep duration must be a number.");
    }
    const int durationMs = static_cast<int>(std::get<double>(args[0]));
    std::this_thread::sleep_for(std::chrono::milliseconds(durationMs));
    return std::monostate{};
}

Value nativeGetEnv(VM& vm, const int argc, const Value* args)
{
    if (argc < 1 || !std::holds_alternative<Obj*>(args[0]) ||
        dynamic_cast<ObjString*>(std::get<Obj*>(args[0])) == nullptr)
    {
        throw std::runtime_error("Environment variable name must be a string.");
    }
    const auto* varName = dynamic_cast<ObjString*>(std::get<Obj*>(args[0]));
    const char* value = std::getenv(varName->chars.c_str());
    if (value == nullptr)
    {
        return vm.newString("");
    }
    return vm.newString(std::string(value));
}

Value nativeSetEnv(VM& vm, const int argc, const Value* args)
{
    if (argc < 2 ||
        !std::holds_alternative<Obj*>(args[0]) ||
        dynamic_cast<ObjString*>(std::get<Obj*>(args[0])) == nullptr ||
        !std::holds_alternative<Obj*>(args[1]) ||
        dynamic_cast<ObjString*>(std::get<Obj*>(args[1])) == nullptr)
    {
        throw std::runtime_error("Environment variable name and value must be strings.");
    }
    const auto* varName = dynamic_cast<ObjString*>(std::get<Obj*>(args[0]));
    const auto* varValue = dynamic_cast<ObjString*>(std::get<Obj*>(args[1]));
    if (setenv(varName->chars.c_str(), varValue->chars.c_str(), 1) != 0)
    {
        throw std::runtime_error("Failed to set environment variable.");
    }
    return std::monostate{};
}

Value nativeExit(VM& vm, const int argc, const Value* args)
{
    int exitCode = 0;
    if (argc >= 1 && std::holds_alternative<double>(args[0]))
    {
        exitCode = static_cast<int>(std::get<double>(args[0]));
    }
    std::exit(exitCode);
}

Value nativeSetTimeout(VM& vm, const int argc, const Value* args)
{
    if (argc < 2 || !isObjType(args[0], ObjType::CLOSURE) || !std::holds_alternative<double>(args[1]))
    {
        throw std::runtime_error("setTimeout requires a function and a delay in milliseconds.");
    }

    auto* callback = dynamic_cast<ObjClosure*>(std::get<Obj*>(args[0]));
    const int delayMs = static_cast<int>(std::get<double>(args[1]));

    // 定时器线程添加任务
    std::future<void> future = std::async(std::launch::async, [&vm, callback, delayMs]()
    {
        // 等待指定的延迟
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));

        // 检查事件循环是否还在运行
        if (!vm.eventLoopRunning) return;

        {
            std::lock_guard lock(vm.eventQueueMutex);
            EventTask task;
            task.callback = callback;
            task.executeTime = getNowMillis() + delayMs;
            task.isInterval = false;
            vm.eventQueue.push(task);
        }
        vm.eventQueueCV.notify_one();
    });

    std::lock_guard lock(vm.asyncTasksMutex);
    vm.asyncTasks.push_back(std::move(future));

    return std::monostate{};
}

Value nativeSetInterval(VM& vm, const int argc, const Value* args)
{
    if (argc < 2 || !isObjType(args[0], ObjType::CLOSURE) || !std::holds_alternative<double>(args[1]))
    {
        throw std::runtime_error("setInterval requires a function and an interval in milliseconds.");
    }

    // 生成唯一的定时器 ID
    const std::string intervalId = "interval_" + std::to_string(getNowMicros());

    auto* callback = dynamic_cast<ObjClosure*>(std::get<Obj*>(args[0]));
    const int intervalMs = static_cast<int>(std::get<double>(args[1]));

    // 注册 interval ID
    {
        std::lock_guard lock(vm.intervalIdsMutex);
        vm.intervalIds.insert(intervalId);
    }

    // 定时器线程循环添加任务
    std::future<void> future = std::async(std::launch::async, [&vm, callback, intervalMs, intervalId]()
    {
        while (true)
        {
            // 检查是否还在活动
            {
                std::lock_guard lock(vm.intervalIdsMutex);
                if (!vm.intervalIds.contains(intervalId))
                {
                    break; // 定时器被清除，退出
                }
            }

            // 等待指定的间隔
            std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));

            // 再次检查是否还在活动（等待期间可能被清除）
            {
                std::lock_guard lock(vm.intervalIdsMutex);
                if (!vm.intervalIds.contains(intervalId))
                {
                    break; // 定时器被清除，退出
                }
            }

            // 检查事件循环是否还在运行
            if (!vm.eventLoopRunning) break;

            // 将任务放入事件队列
            {
                std::lock_guard lock(vm.eventQueueMutex);
                EventTask task;
                task.callback = callback;
                task.executeTime = getNowMillis();
                task.isInterval = true;
                task.intervalId = intervalId;
                task.intervalMs = intervalMs;
                vm.eventQueue.push(task);
            }
            vm.eventQueueCV.notify_one();
        }
    });

    std::lock_guard lock(vm.asyncTasksMutex);
    vm.asyncTasks.push_back(std::move(future));

    return vm.newString(intervalId);
}

Value nativeClearInterval(VM& vm, const int argc, const Value* args)
{
    if (argc < 1 || !std::holds_alternative<Obj*>(args[0]) ||
        dynamic_cast<ObjString*>(std::get<Obj*>(args[0])) == nullptr)
    {
        throw std::runtime_error("Interval ID must be a string.");
    }
    {
        const auto* intervalId = dynamic_cast<ObjString*>(std::get<Obj*>(args[0]));
        std::lock_guard lock(vm.intervalIdsMutex);
        vm.intervalIds.erase(intervalId->chars);
    }
    return std::monostate{};
}
