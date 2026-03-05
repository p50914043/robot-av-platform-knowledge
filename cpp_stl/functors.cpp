#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 定义仿函数：降序排序
struct DescSort {
  bool operator()(int a, int b) {
    return a > b;
  }
};

int main() {
  vector<int> nums = {3, 1, 4, 2};
  sort(nums.begin(), nums.end(), DescSort());  // 传入仿函数
  for (int num : nums) {
    cout << num << " ";  // 输出：4 3 2 1
  }
  return 0;
}