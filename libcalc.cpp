//
// Created by oddgeir on 1/26/25.
//
#include <iostream>
#include <queue>
#include "libcalc.h"

namespace libcalc {
double add(double a, double b) {
    return a+b;
}

double sub(double a, double b) {
    return a-b;
}

double mult(double a, double b) {
    return a*b;
}

double div(double a, double b) {
    return a/b;
}

bool isNumber(char c) {
    switch (c) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
    case '.':
        return true;
    default:
        return false;

    }
}

bool isOperator(char character) {
    switch(character) {
    case '+':
    case '-':
    case '*':
    case '/':
        return 1;
    default:
        return 0;
    }
}

bool isPlusMinusOperator(char character) {
    switch(character) {
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

typedef struct {
    std::string operand;
    size_t offset;
} UnwrapedExpression;

UnwrapedExpression unwrap(std::string expression) {
    UnwrapedExpression result;
    int depth = 0;
    for(unsigned int i = 0; i < expression.size(); i++) {
        if (expression.at(i) == '(') {
            depth++;
            continue;
        } else if (expression.at(i) == ')') {
            depth--;
            if (depth == 0) {
                result = {
                          expression.substr(1, i-1),
                    i+1
                };
                return result;
            }
        }
    }
    if (depth == 0) {
        return {expression,expression.size()};
    } else {
        std::cout << "Parenthesis mismatch!";
        exit(1);
    }
}

double calculate(std::string expression) {
    std::cout << "Calculate expression: " << expression << std::endl;
    std::queue<std::string> operands;
    std::queue<std::string> operations;

    bool onlyDigits = true;
    std::string temp_operand = "";
    int offset = 0;
    for(long unsigned int index = 0; index < expression.size(); index++) {
        char character = expression.at(index);
        //cout << "Character: " << character << endl;
        if (character == '(') {
            UnwrapedExpression unwraped = unwrap(expression.substr(index));
            operands.push(unwraped.operand);
            offset += unwraped.offset;
            index += unwraped.offset - 1;
            temp_operand = "";
            onlyDigits = false;
        } else if (character == '*') {
            if (temp_operand != "") {
                operands.push(temp_operand);
                operations.push("mult");
                offset = index + 1;
                temp_operand = "";
                onlyDigits = false;
            } else {
                operations.push("mult");
                offset = index + 1;
                onlyDigits = false;
            }
        } else if (character == '/') {
            if (temp_operand != "") {
                operands.push(temp_operand);
                operations.push("div");
                offset = index + 1;
                temp_operand = "";
                onlyDigits = false;
            } else {
                operations.push("div");
                offset = index + 1;
                onlyDigits = false;
            }
        } else if (isNumber(character) || isPlusMinusOperator(character)) {
            temp_operand += character;
        }
        if(index == expression.size() - 1 && operands.size() == operations.size()) {
            operands.push(temp_operand);
        }
    }
    if (onlyDigits) {
        std::cout << "STOD operand: " << temp_operand << std::endl;
        return stod(temp_operand);
    } else {
        std::cout << "Operands: " << operands.size() << " Operations: " << operations.size() << std::endl;
        double accumulator = libcalc::parse(operands.front());
        operands.pop();
        std::string operation;
        std::string operand;
        while(operands.size() > 0) {
            operation = operations.front();
            operations.pop();

            operand = operands.front();
            operands.pop();

            std::cout << accumulator << " " << operation << " " << operand << "\n";
            if (operation == "mult") {
                accumulator = mult(accumulator, libcalc::parse(operand));
            } else if (operation == "div") {
                accumulator = div(accumulator, libcalc::parse(operand));
            }
        }
        return accumulator;
    }
}
double parse(std::string expression) {
    std::cout << "Parse expression: " << expression << "\n";
    std::queue<std::string> operands;
    std::queue<std::string> operations;
    int depth = 0;

    int offset = 0;
    for(long unsigned int index = 0; index < expression.size(); index++) {
        char character = expression.at(index);
        if (character == '+') {
            if (depth == 0) {
                operands.push(expression.substr(offset,index-offset));
                operations.push("add");
                offset = index + 1;
            }
        } else if (character == '-') {
            if (depth == 0) {
                operands.push(expression.substr(offset,index-offset));
                operations.push("sub");
                offset = index + 1;
            }
        } else if (character == '(') {
            depth++;
        } else if (character == ')') {
            depth--;
        }
        if(index == expression.size() - 1) {
            operands.push(expression.substr(offset,index-offset+1));
        }
    }

    double accumulator = calculate(operands.front());
    operands.pop();

    std::string operation;
    std::string operand;
    while(operands.size() > 0) {
        operation = operations.front();
        operations.pop();

        operand = operands.front();
        operands.pop();

        std::cout << accumulator << " " << operation << " " << operand << "\n";
        if (operation == "add") {
            accumulator = add(accumulator, calculate(operand));
        } else if (operation == "sub") {
            accumulator = sub(accumulator, calculate(operand));
        }
    }

    return accumulator;
}

std::string trimWhitespace(std::string expression) {
    std::string trimmedExpression = "";
    std::cout << "Size of expression: " << expression.size() << "\n";
    for (unsigned int i = 0; i < expression.size(); i++) {
        char character = expression.at(i);
        std::cout << "Character: " << character << std::endl;
        if (!isspace(character)) {
            trimmedExpression += character;
        }
    }
    std::cout << "Trimmed expression: " << trimmedExpression << std::endl;
    return trimmedExpression;
}

bool verifySymbols(std::string expression) {
    for (unsigned int i = 0; i < expression.size(); i++) {
        char character = expression.at(i);
        if(!(libcalc::isNumber(character) || libcalc::isOperator(character) || character == '(' || character == ')')) {
            return 0;
        }
    }
    return 1;
}
std::string expandExpression(std::string expression) {
    for (unsigned int i = 0; i < expression.size(); i++) {
        char character = expression.at(i);
        //cout << "Expanding: " << character << endl;
        if (character == '(' && i > 0 && (libcalc::isNumber(expression.at(i-1)) || expression.at(i-1) == ')')) {
            expression.insert(i, "*");
            i++;
        }
    }
    std::cout << "Expanded expression: " << expression << std::endl;
    return expression;
}

std::string evaluate(std::string expression) {
    std::string trimmedExpression = trimWhitespace(expression);
    if (verifySymbols(trimmedExpression)) {
        std::string expandedExpression = expandExpression(trimmedExpression);
        return std::to_string(libcalc::parse(expandedExpression));
    } else {
        std::cerr << "Invalid expression: " << expression << std::endl;
        exit(1);
    }
}

}
