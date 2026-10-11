#include <iostream>
#include <limits>

int main()
{
  const int calculation_error_return_code = 2;
  int num = 0;
  std::cin >> num;
  if (!std::cin) {
    std::cerr << "ERROR: input is not a secuence\n";
    return 1;
  }

  int countAllElem = 0;
  int firstMax = num;
  int secondMax = std::numeric_limits< int >::min();
  int count = 0;
  int lastElem = 0;
  int maxCount = 0;
  bool hasSecondMax = false;

  if (num == 0) {
    std::cerr << "ERROR: too short sequence\n";
    std::cout << maxCount << '\n';
    return calculation_error_return_code;
  }

  count = 1;
  maxCount = 1;
  countAllElem = 1;
  lastElem = num;

  while (std::cin >> num && num != 0) {
    countAllElem++;

    if (num > firstMax) {
      secondMax = firstMax;
      firstMax = num;
      hasSecondMax = true;
    } else if (num < firstMax && num > secondMax) {
      secondMax = num;
      hasSecondMax = true;
    }

    if (num <= lastElem) {
      count++;
      if (count > maxCount) {
        maxCount = count;
      }
    } else {
      count = 1;
    }
    lastElem = num;
  }

  if (!std::cin) {
    std::cerr << "ERROR: input is not a sequence\n";
    return 1;
  }

  if (!hasSecondMax) {
    std::cerr << "ERROR: sequence do not have second maximum\n";
    std::cout << maxCount << '\n';
    return calculation_error_return_code;
  }

  if (countAllElem < 2) {
    std::cerr << "ERROR: too short sequence\n";
    std::cout << maxCount << '\n';
    return calculation_error_return_code;
  }

  std::cout << secondMax << '\n';
  std::cout << maxCount << '\n';

  return 0;
}
