#include "parser.h"
#include <sstream>
#include <regex>

PowrParser::PowrParser(const std::string& source) : source(source) {}

std::vector<Function> PowrParser::parse() {
    std::vector<Function> functions;
    std::istringstream stream(source);
    std::string line;
    Function currentFunction;

    while (std::getline(stream, line)) {
        std::string strippedLine = line;
        strippedLine.erase(remove_if(strippedLine.begin(), strippedLine.end(), isspace), strippedLine.end());

        if (strippedLine.find("func") == 0) {
            if (!currentFunction.name.empty()) {
                functions.push_back(currentFunction);
            }
            currentFunction = Function{extractFunctionName(strippedLine), {}};
        } else if (!currentFunction.name.empty()) {
            if (strippedLine == "return;") {
                currentFunction.body.push_back({"return", ""});
            } else {
                currentFunction.body.push_back(parseStatement(strippedLine));
            }
        }
    }

    if (!currentFunction.name.empty()) {
        functions.push_back(currentFunction);
    }

    return functions;
}

std::string PowrParser::extractFunctionName(const std::string& line) {
    std::regex regex(R"(func\s*{([^}]+)})");
    std::smatch match;
    if (std::regex_search(line, match, regex)) {
        return match[1].str();
    }
    return "";
}

Statement PowrParser::parseStatement(const std::string& line) {
    if (line.find("println") == 0) {
        return {"println", line.substr(8, line.size() - 9)}; // Remove println( and )
    } else if (line.find(".var") == 0) {
        return {"variable_assignment", line.substr(5)}; // Remove .var
    }
    return {"unknown", line};
}
