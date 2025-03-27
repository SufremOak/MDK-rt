#ifndef POWR_COMPILER_H
#define POWR_COMPILER_H

#include "parser.h"
#include <string>
#include <vector>

class PowrCompiler {
public:
    explicit PowrCompiler(const std::vector<Function>& functions);
    std::string compile();
    bool generateExecutable(const std::string& cppCode, const std::string& outputFile);

private:
    std::vector<Function> functions;
    void compileFunction(const Function& function, std::string& cppCode);
    void compileStatement(const Statement& stmt, std::string& cppCode);
};

#endif // POWR_COMPILER_H
