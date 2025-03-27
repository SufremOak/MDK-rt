#include "compiler.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>

PowrCompiler::PowrCompiler(const std::vector<Function>& functions) : functions(functions) {}

std::string PowrCompiler::compile() {
    std::string cppCode = "#include <iostream>\n\n";
    cppCode += "using namespace std;\n\n";

    for (const auto& function : functions) {
        compileFunction(function, cppCode);
    }

    return cppCode;
}

void PowrCompiler::compileFunction(const Function& function, std::string& cppCode) {
    cppCode += "void " + function.name + "() {\n";
    for (const auto& stmt : function.body) {
        compileStatement(stmt, cppCode);
    }
    cppCode += "}\n";
}

void PowrCompiler::compileStatement(const Statement& stmt, std::string& cppCode) {
    if (stmt.type == "println") {
        cppCode += "    cout << " + stmt.value + " << endl;\n";
    } else if (stmt.type == "variable_assignment") {
        std::string varName = stmt.value.substr(0, stmt.value.find(' '));
        std::string varValue = stmt.value.substr(stmt.value.find(' ') + 1);
        cppCode += "    std::string " + varName + " = " + varValue + ";\n";
    } else if (stmt.type == "return") {
        cppCode += "    return;\n";
    }
}

bool PowrCompiler::generateExecutable(const std::string& cppCode, const std::string& outputFile) {
    // Write the C++ code to a temporary file
    std::string tempFileName = "temp_powr_code.cpp";
    std::ofstream outFile(tempFileName);
    if (!outFile) {
        std::cerr << "Error creating temporary file." << std::endl;
        return false;
    }
    outFile << cppCode;
    outFile.close();

    // Compile the C++ code using g++
    std::string command = "g++ " + tempFileName + " -o " + outputFile;
    int result = std::system(command.c_str());

    // Clean up the temporary file
    std::remove(tempFileName.c_str());

    return result == 0; // Return true if compilation was successful
}
