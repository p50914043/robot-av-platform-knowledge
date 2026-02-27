#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <vector>

class Obj {
 public:
  Obj(int i) : i_(i) {}
  ~Obj() {}

  Obj(const Obj&) = delete;
  Obj& operator=(const Obj&) = delete;

 private:
  int i_;
};

int main() {
  std::vector<Obj> vec;
  auto now = std::chrono::steady_clock::now();
  for (int i = 0; i < 2000000; i++) {
    vec.push_back(Obj(i));  // 当size 等于 capacity 时，会增加一倍的 capacity
    // std::cout << "size: " << vec.size() << std::endl;
    // std::cout << "capacity: " << vec.capacity() << std::endl;
  }
  auto end = std::chrono::steady_clock::now();
  auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - now);
  std::cout << "time: " << diff.count() << " ms" << std::endl;

  now = std::chrono::steady_clock::now();
  for (int i = 0; i < 2000000; i++) {
    vec.emplace_back(i);  // 当size 等于 capacity 时，会增加一倍的 capacity
    // std::cout << "size: " << vec.size() << std::endl;
    // std::cout << "capacity: " << vec.capacity() << std::endl;
  }
  end = std::chrono::steady_clock::now();
  diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - now);
  std::cout << "time: " << diff.count() << " ms" << std::endl;

  return 0;
}

// 测试结果:
// ./a.out
// time: 83 ms
// time: 60 ms