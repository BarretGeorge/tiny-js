#include <string>
#include "object.h"
#include "scanner.h"
#include "parser.h"
#include "compiler.h"
#include "native/require.h"

constexpr auto MAIN_FILE = "main.js";

int main(int argc, char* argv[])
{
    VM vm;
    vm.initModule();
    std::string entryFile = MAIN_FILE;
    if (argc > 1)
    {
        entryFile = argv[1];
    }

    if (std::string source = readFile(entryFile); !source.empty())
    {
        Scanner scanner(source);
        auto tokens = scanner.scanTokens();
        Parser parser(tokens);
        auto stmts = parser.parse();
        Compiler compiler(vm);
        ObjFunction* script = compiler.compile(stmts);
        vm.interpret(script);
    }
}
