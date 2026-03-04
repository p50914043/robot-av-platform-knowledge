#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main() {
  int a = 0;
  auto f = [a](int x) mutable -> int {
    a++;
    return x * x;
  };

  return 0;
}
