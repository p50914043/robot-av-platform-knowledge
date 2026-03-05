// placement new 是 C++ 中的一种内存分配方式，它可以在已分配的内存中构造对象，而不是在堆上分配新的内存。

#include <iostream>
#include <new>
class Test {
 public:
  Test() {
    std::cout << "Constructor called" << std::endl;
  }
  ~Test() {
    std::cout << "Destructor called" << std::endl;
  }
  void* operator new(size_t size, void* ptr) {
    return ptr;
  }
};

int main() {
  Test* t = new (malloc(sizeof(Test))) Test();
  std::cout << "t: " << t << std::endl;
  void* ptr = malloc(sizeof(Test));
  std::cout << "ptr: " << ptr << std::endl;
  Test* t2 = new (ptr) Test();
  std::cout << "t2: " << t2 << std::endl;
  delete t;
  delete t2;
  return 0;
}
