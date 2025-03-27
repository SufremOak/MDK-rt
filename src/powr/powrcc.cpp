#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "parser.hpp"
#include "compiler.hpp"

void executePowrScript(const std::string& script) {
    PowrParser parser(script);
    std::vector<Function> functions = parser.parse();
    PowrCompiler compiler(functions);
    std::string cppCode = compiler.compile();

    std::cout << "Compiled C++ Code:\n";
    std::cout << cppCode << std::endl;

    // Generate executable
    std::string outputFile = "powr_executable";
    if (compiler.generateExecutable(cppCode, outputFile)) {
        std::cout << "Compilation successful. Executable created: " << outputFile << std::endl;

        // Execute the generated executable
        std::system(("./" + outputFile).c_str());
    } else {
        std::cerr << "Compilation failed." << std::endl;
    }
}

std::string readPowrFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return script;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: powrcc <filename.pwr> [--jit]" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filename = argv[1];
    bool jit = (argc > 2 && std::string(argv[2]) == "--jit");

    std::string powrScript = readPowrFile(filename);
    std::cout << "Welcome to Powr Compiler\n";

    if (jit) {
        executePowrScript(powrScript);
    } else {
        std::cout << "Compilation without execution is not yet implemented." << std::endl;
    }

    return EXIT_SUCCESS;
}
