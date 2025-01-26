//
// Created by oddgeir on 1/25/25.
//
#include <iostream>

#ifndef LIBCALC_H
#define LIBCALC_H

namespace libcalc {
  bool isNumber(char);

  bool isOperator(char character);

  double parse(std::string);

  double calculate(std::string);
}

#endif //LIBCALC_H
