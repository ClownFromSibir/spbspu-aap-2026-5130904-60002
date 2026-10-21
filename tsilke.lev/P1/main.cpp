#include <iostream>

int main()
{
  int number(0);
  int currentValue;
  int value1;
  int value2;
  int value3;
  int count11(0);
  int count15(0);
  std::cout << "Enter values of sequence:\n";
  while (true)
  {
    std::cin >> currentValue;
    if (std::cin.fail())
    {
      std::cerr << "Invalid input\n";
      return 1;
    }
    if (currentValue == 0)
    {
      break;
    }
    number++;
    switch (number)
    {
      case 1:
        value1 = currentValue;
        break;
      case 2:
        value2 = currentValue;
        break;
      case 3:
        value3 = currentValue;
        break;
      default:
        value1 = value2;
        value2 = value3;
        value3 = currentValue;
        break;
    }
    if (number >= 2)
    {
      if (value2 % value1 == 0)
      {
        count11++;
      }
    }
    if (number >= 3)
    {
      if (value3 == value1 + value2)
      {
        count15++;
      }
    }
  }
  if (number < 2)
  {
    std::cerr << "11: There must be at least two elements\n";
    std::cerr << "15: There must be at least three elements\n";
    return 2;
  }
  std::cout << "11: " << count11 << "\n";
  if (number < 3)
  {
    std::cerr << "15: There must be at least three elements\n";
    return 2;
  }
  std::cout << "15: " << count15 << "\n";
  return 0;
}
