#include <iostream>
#include <iterator>
#include <vector>

// 迭代器类型，分为输入迭代器、输出迭代器、前向迭代器、双向迭代器、随机访问迭代器
// 输入迭代器: 只能读取，不能写入，只能单向移动
int main() {
  std::cout << "请输入若干整数：\n";
  // 直接用istream_iterator范围初始化vector
  std::vector<int> nums(std::istream_iterator<int>(std::cin),  // 起始迭代器
                        std::istream_iterator<int>()           // 结束迭代器
  );

  std::cout << "读取到的整数：";
  for (int num : nums) {
    std::cout << num << " ";
  }
  return 0;
}