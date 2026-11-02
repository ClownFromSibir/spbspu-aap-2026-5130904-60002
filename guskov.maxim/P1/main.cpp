#include <iostream>

const int INPUT_ERROR_CODE = 1;
const int IMPOSSIBLE_TO_CALCULATE = 2;

int main()
{
  int beforePrevious = 0;
  int previous = 0;
  int current = 0;
  int len = 0;
  int locMinCount = 0;
  int divRemCount = 0;

  while (true) {
    std::cin >> current;

    if (std::cin.fail()) {
      std::cerr << "ERROR: this symbol is not allowed\n";
      return INPUT_ERROR_CODE;
    }
    if (current == 0) {
      break;
    }

    if (len >= 2 && previous < beforePrevious && previous < current) {
      ++locMinCount;
    }
    if (len >= 1 && current % previous == 0) {
      ++divRemCount;
    }

    beforePrevious = previous;
    previous = current;
    ++len;
  }

  int status = 0;

  if (len < 1) {
    std::cerr << "ERROR: array is too short\n";
    return IMPOSSIBLE_TO_CALCULATE;
  } else {
    std::cout << locMinCount << '\n';
  }

  if (len < 2) {
    std::cerr << "ERROR: array is too short\n";
    return IMPOSSIBLE_TO_CALCULATE;
  } else {
    std::cout << divRemCount << '\n';
  }

  return 0;
}