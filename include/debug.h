#ifndef TINY_JS_DEBUG_H
#define TINY_JS_DEBUG_H

#include "common.h"
#include <format>
#include <iostream>
#include <source_location>
#include <string_view>
#include <type_traits>

#ifdef DEBUG
constexpr bool ENABLE_DEBUG = true;
#else
constexpr bool ENABLE_DEBUG = false;
#endif

template <typename... Args>
struct LogMsg
{
    std::format_string<Args...> fmt;
    std::source_location loc;

    consteval LogMsg(const char* s, std::source_location l = std::source_location::current())
        : fmt(s), loc(l)
    {
    }

    consteval LogMsg(std::string_view s, std::source_location l = std::source_location::current())
        : fmt(s), loc(l)
    {
    }
};

template <typename... Args>
void debug_log(LogMsg<std::type_identity_t<Args>...> msg, Args&&... args)
{
    if constexpr (ENABLE_DEBUG)
    {
        std::string str = std::vformat(msg.fmt.get(), std::make_format_args(args...));
        std::cout << "\033[32m";
        std::cout << std::format("[{}:{}] {}\n",
                                 msg.loc.file_name(),
                                 msg.loc.line(),
                                 str);
        std::cout << "\033[0m";
    }
}

#endif //TINY_JS_DEBUG_H
