#include <iostream>

int INPUT_ERROR_CODE = 1;
int IMPOSSIBLE_TO_CALCULATE = 2;

int main()
{
  int previous = 0;
  int current = 0;
  int count = 0;

  while (true)
  {
    previous = current;

    std::cin >> current;

    if (std::cin.fail())
    {
      std::cerr << "ERROR: this symbol is not allowed\n";
      return INPUT_ERROR_CODE;
    }
    
    if (current == 0)
    {
      return 0;
    }

    count++;
  }
}
