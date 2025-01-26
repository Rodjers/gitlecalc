//
// Created by oddgeir on 1/25/25.
//

#ifndef LIBCALC_H
#define LIBCALC_H

#include <string>

namespace libcalc {
  bool isNumber(char);

  bool isOperator(char character);

  double parse(std::string);

  double calculate(std::string);

  std::string evaluate(std::string);
}

#endif //LIBCALC_H
