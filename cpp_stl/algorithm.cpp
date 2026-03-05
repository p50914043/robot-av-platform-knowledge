#include <algorithm>
#include <iostream>
#include <vector>

// 核心分类：
// 非修改型算法：for_each（遍历）、find（查找）、count（计数）
// 修改型算法：copy（复制）、replace（替换）、swap（交换）
// 排序算法：sort（快速排序）、stable_sort（稳定排序）、reverse（反转）
// 数值算法：accumulate（累加）、max_element（找最大值）

int main() {
  std::vector<int> v = {1, 2, 3, 4, 42, 42, 42, 5};
  std::cout << std::count(std::begin(v), std::end(v), 42) << '\n';  // 计算跟42相等的元素个数
  std::reverse(std::begin(v), std::end(v));                         // 反转v
  for (int i : v) {
    std::cout << i << ' ';
  }
  return 0;
}
