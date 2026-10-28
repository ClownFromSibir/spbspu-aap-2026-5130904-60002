#include <iostream>

int main()
{
  const int WRONG_INPUT = 1;
  const int EMPTY_SEQUENCE = 2;
  int current = 0;
  std::cin >> current;
  if (!std::cin)
  {
    std::cerr << "Error: invalid input" << "\n";
    return WRONG_INPUT;
  }
  if (current == 0)
  {
    std::cerr << "Error: sequence is empty" << "\n";
    std::cout << 0 << "\n";
    return EMPTY_SEQUENCE;
  }

  int maxValue = current;
  int afterMax = 0;
  int minValue = current;
  int minCount = 1;
  while (std::cin >> current)
  {
    if (current == 0)
    {
      break;
    }
    if (current > maxValue)
    {
      maxValue = current;
      afterMax = 0;
    }
    else
    {
      afterMax++;
    }
    if (current < minValue)
    {
      minValue = current;
      minCount = 1;
    }
    else if (current == minValue)
    {
      minCount++;
    }
  }
  if (!std::cin)
  {
    std::cerr << "Error: invalid sequence" << "\n";
    return WRONG_INPUT;
  }
  std::cout << afterMax << "\n";
  std::cout << minCount << "\n";
  return 0;
}
