#include <iostream>

using namespace std;

template <int N>
struct Fibonacci {
  static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

// 全特化
template <>
struct Fibonacci<0> {
  static constexpr int value = 0;
};

// 模板元编程
template <typename T>
T add(T a, T b) {
  return a + b;
}

// 1. 重载doAdvance，适配不同迭代器类别
// 随机访问迭代器：直接用+=
template <typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::random_access_iterator_tag) {
  iter += d;
}

// 双向迭代器：循环++/--
template <typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::bidirectional_iterator_tag) {
  if (d >= 0) {
    while (d--) ++iter;
  } else {
    while (d++) --iter;
  }
}

// 输入/前向迭代器：仅正向，负距离抛异常
template <typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::input_iterator_tag) {
  if (d < 0) {
    throw std::out_of_range("输入/前向迭代器不支持负距离移动");
  }
  while (d--) ++iter;
}

// 2. 主函数：通过iterator_traits获取迭代器类别，调用对应重载
template <typename IterT, typename DistT>
void myAdvance(IterT& iter, DistT d) {
  doAdvance(iter, d, typename std::iterator_traits<IterT>::iterator_category());  // 调用对应重载
}


// typename std::iterator_traits<IterT>::iterator_category() 获取迭代器类别
int main() {
  cout << Fibonacci<10>::value << endl;
  cout << add(1, 2) << endl;
  cout << add(1.1, 2.2) << endl;
  return 0;
}