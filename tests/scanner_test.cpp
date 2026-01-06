#include <iostream>
#include "scanner.h"

constexpr auto SCRIPT = R"(
    let str = "Hello, ";
    fun greet(name) {
        return str + name + "!";
    }
    print(greet("World"));

    var str = "Count: ";
    for(var i = 0; i < 5; i = i + 1) {
        str = str + i;
        print(str);
    }

    str = "当前时间戳=" + now();
    print(str);

    class Foo {
        fun method() {
            print "This is a method.";
        }
    }
)";

std::string tokenToString(const Token& type)
{
    return "Line " + std::to_string(type.line) + " " + std::to_string(static_cast<int>(type.type)) + " '" + type.lexeme
        + "'";
}

int main()
{
    Scanner scanner(SCRIPT);
    for (const auto tokens = scanner.scanTokens(); const auto& token : tokens)
    {
        std::cout << tokenToString(token) << std::endl;
    }
}
