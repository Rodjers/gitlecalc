#include <iostream>
#include <queue>
#include <locale>
#include "libcalc/libcalc.h"

using namespace std;

string trimWhitespace(string expression) {
  string trimmedExpression = "";
  cout << "Size of expression: " << expression.size() << "\n";
  for (unsigned int i = 0; i < expression.size(); i++) {
    char character = expression.at(i);
    cout << "Character: " << character << endl;
    if (!isspace(character)) {
      trimmedExpression += character;
    }
  }
  cout << "Trimmed expression: " << trimmedExpression << endl;
  return trimmedExpression;
}

bool verifySymbols(string expression) {
  for (unsigned int i = 0; i < expression.size(); i++) {
    char character = expression.at(i);
    if(!(libcalc::isNumber(character) || libcalc::isOperator(character) || character == '(' || character == ')')) {
      return 0;
    }
  }
  return 1;
}
string expandExpression(string expression) {
  for (unsigned int i = 0; i < expression.size(); i++) {
    char character = expression.at(i);
    //cout << "Expanding: " << character << endl;
    if (character == '(' && i > 0 && (libcalc::isNumber(expression.at(i-1)) || expression.at(i-1) == ')')) {
      expression.insert(i, "*");
      i++;
    }
  }
  cout << "Expanded expression: " << expression << endl;
  return expression;
}

double evaluate(string expression) {
  string trimmedExpression = trimWhitespace(expression);
  if (verifySymbols(trimmedExpression)) {
    string expandedExpression = expandExpression(trimmedExpression);
    return libcalc::parse(expandedExpression);
  } else {
    cerr << "Invalid expression: " << expression << endl;
    exit(1);
  }
}

int main() {

  int done = 0;
  while(!done) {
    cout << "Enter math: ";
    string input;
    std::getline(std::cin, input);
    if(input == "q") {
      done = 1;
    } else {
      //      cout << "You entered:\n";
      double result = evaluate(input);
      cout << "Result: " << result << "\n";
    }
  }
  return 0;
}
