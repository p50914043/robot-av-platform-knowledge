#include <iostream>
#include <map>
// 初始化map然后遍历
int main() {
  std::map<int, int> m;
  m[1] = 2;
  m[2] = 3;
  m[3] = 4;
  m[4] = 5;
  m[5] = 6;
  m[6] = 7;
  m[7] = 8;
  m[8] = 9;
  m[9] = 10;
  for (auto it = m.begin(); it != m.end(); it++) {
    std::cout << it->first << " " << it->second << std::endl;
  }
}