#include <iostream>
#include <queue>
#include <locale>

using namespace std;

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

double parse(string);
double calculate(string);

typedef struct {
  string expression;
} Parser;

typedef struct {
  double operand1;
  double operand2;
  double (*operato) (double,double);
} Operation;

typedef struct {
  string operand;
  size_t offset;
} UnwrapedExpression;

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

UnwrapedExpression unwrap(string expression) {
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
    cout << "Parenthesis mismatch!";
    exit(1);
  }
}

double calculate(string expression) {
  cout << "Calculate expression: " << expression << endl;
  queue<string> operands;
  queue<string> operations;

  bool onlyDigits = true;
  string temp_operand = "";
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
      cout << "STOD operand: " << temp_operand << endl;
    return stod(temp_operand);
  } else {
    cout << "Operands: " << operands.size() << " Operations: " << operations.size() << endl;
    double accumulator = parse(operands.front());
    operands.pop();
    string operation;
    string operand;
    while(operands.size() > 0) {
        operation = operations.front();
        operations.pop();

        operand = operands.front();
        operands.pop();

        cout << accumulator << " " << operation << " " << operand << "\n";
        if (operation == "mult") {
          accumulator = mult(accumulator, parse(operand));
        } else if (operation == "div") {
          accumulator = div(accumulator, parse(operand));
        }
    }
    return accumulator;
  }
}

double parse(string expression) {
  cout << "Parse expression: " << expression << "\n";
  queue<string> operands;
  queue<string> operations;
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

  string operation;
  string operand;
  while(operands.size() > 0) {
    operation = operations.front();
    operations.pop();

    operand = operands.front();
    operands.pop();

    cout << accumulator << " " << operation << " " << operand << "\n";
    if (operation == "add") {
      accumulator = add(accumulator, calculate(operand));
    } else if (operation == "sub") {
      accumulator = sub(accumulator, calculate(operand));
    }
  }

  return accumulator;
}

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
    if(!(isNumber(character) || isOperator(character) || character == '(' || character == ')')) {
      return 0;
    }
  }
  return 1;
}
string expandExpression(string expression) {
  for (unsigned int i = 0; i < expression.size(); i++) {
    char character = expression.at(i);
    //cout << "Expanding: " << character << endl;
    if (character == '(' && i > 0 && (isNumber(expression.at(i-1)) || expression.at(i-1) == ')')) {
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
    return parse(expandedExpression);
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
