#include <iostream>
int main() {
  int lenMonDecreas = 0;
  int mxLenMonDec = lenMonDecreas;
  int lenChangeSign = 0;
  int mxLenChangeSign = lenChangeSign;
  int curr = 0;

  while (true) {
    int secToLast = curr;
    if (!(std::cin >> curr)) {
      std::cerr << "Invalid argument!\n";
      return 1;
    } else if (curr == 0) {
      break;
    } else {
      if (curr <= secToLast) {
        lenMonDecreas++;
        if (lenMonDecreas > mxLenMonDec) {
          mxLenMonDec = lenMonDecreas;
        }
      } else {
        lenMonDecreas = 1;
      }

      if ((curr > 0 && secToLast < 0) || (curr < 0 && secToLast > 0)) {
        lenChangeSign++;
        if (lenChangeSign > mxLenChangeSign) {
          mxLenChangeSign = lenChangeSign;
        }
      } else {
        lenChangeSign = 0;
      }
    }
  }
  std::cout << "#5 Max lenght mon. - decreas. series = " << mxLenMonDec << "\n";
  std::cout << "#9 Max count change sign = " << mxLenChangeSign;
  return 0;
}