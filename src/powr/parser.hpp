#ifndef POWR_PARSER_H
#define POWR_PARSER_H

#include <string>
#include <vector>
#include <unordered_map>

struct Statement {
    std::string type;
    std::string value;
};

struct Function {
    std::string name;
    std::vector<Statement> body;
};

class PowrParser {
public:
    explicit PowrParser(const std::string& source);
    std::vector<Function> parse();

private:
    std::string source;
    std::string extractFunctionName(const std::string& line);
    Statement parseStatement(const std::string& line);
};

#endif // POWR_PARSER_H
