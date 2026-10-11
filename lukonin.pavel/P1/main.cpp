#include <iostream>

int main()
{
  int n;
  std::cin >> n;
  if (std::cin.fail())
  {
    return 1;
  }
  if (n == 0)
  {
    std::cout << 0 << "\n";
    return 0;
  }

  int max = n;
  int count = 1;

  while (true)
  {
    std::cin >> n;
    if (std::cin.fail())
    {
      return 1;
    }
    if (n == 0)
    {
      std::cout << count << "\n";
      return 0;
    }
    if (n == max)
    {
      count++;
    }
    else if (n > max)
    {
      max = n;
      count = 1;
    }
  }

  return 0;
}
