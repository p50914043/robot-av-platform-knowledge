
//  容器适配器
// #include <iostream>
// #include <queue>
// #include <stack>
// int main() {
//   std::stack<int> s;  // 容器适配器：基于deque封装栈
//   s.push(10);
//   s.push(20);
//   std::cout << "栈顶：" << s.top() << std::endl;  // 10
//   s.pop();

//   std::queue<int> q;  // 容器适配器：基于deque封装队列
//   q.push(20);
//   q.push(30);
//   std::cout << "队首：" << q.front() << std::endl;  // 20
//   q.pop();
//   return 0;
// }

// 迭代器适配器
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
int main() {
  std::vector<int> vec = {1, 2, 3};
  // 反向迭代器适配器：反向遍历
  for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
    std::cout << *it << " ";  // 3 2 1
  }

  //   std::back_inserter是 STL 中的迭代器适配器（属于输出迭代器），核心作用是： 封装一个支持push_back()
  //   的容器，返回一个std::back_insert_iterator对象；当通过这个迭代器赋值时，会自动调用容器的push_back()
  //   方法 向容器尾部插入元素。 它的核心价值是：让 STL算法（如std::copy、std::transform）直接向容器尾部插入元素，
  //     无需手动调用push_back()，也无需提前预留容器大小。
  // 尾插迭代器适配器：配合copy算法插入元素
  std::vector<int> vec2;
  std::copy(vec.begin(), vec.end(),
            std::back_inserter(vec2));  // std::back_inserter 尾插迭代器，通过调用push_back，实现尾插
  for (auto it = vec2.rbegin(); it != vec2.rend(); ++it) {
    std::cout << *it << " ";  // 3 2 1
  }
  return 0;
}

// #include <algorithm>
// #include <functional>
// #include <iostream>
// #include <vector>

// int add(int a, int b) {
//   return a + b;
// }
// int main() {
//   // bind适配器：绑定add的第二个参数为5，适配成单参数函数
//   auto add5 = std::bind(add, std::placeholders::_1, 5);
//   std::cout << add5(10) << std::endl;  // 15

//   // not_fn适配器：取反判断条件，适配find_if算法
//   std::vector<int> nums = {1, 2, 3};
//   auto it = std::find_if(nums.begin(), nums.end(), std::not_fn([](int n) { return n % 2 == 1; }));
//   std::cout << *it << std::endl;  // 2（第一个偶数）
//   return 0;
// }