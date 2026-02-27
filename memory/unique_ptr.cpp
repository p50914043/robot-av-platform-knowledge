#include <iostream>
#include <memory>

// 手动实现一个简单的 unique_ptr 类：
// 禁止拷贝构造函数和拷贝赋值运算符
// 需要实现移动构造函数和移动赋值运算符
// 实现以下接口：
// 1. 构造函数
// 2. 析构函数
// 3. 移动构造函数
// 4. 移动赋值运算符
// 5. get() 方法
// 6. release() 方法
// 6. operator*() 方法
// 7. operator->() 方法
template <typename T>
class UniquePtr {
 public:
  UniquePtr(T *ptr = nullptr) : ptr_(ptr) {}
  ~UniquePtr() { delete ptr_; }

  /*
   * 移动赋值运算符*/
  UniquePtr &operator=(UniquePtr &&other) {
    delete ptr_;
    ptr_ = other.release();
    return *this;
  }

  T &operator*() { return *ptr_; }

  T *operator->() { return ptr_; }

  T *release() {
    T *temp = ptr_;
    ptr_ = nullptr;
    return temp;
  }

  T *get() const { return ptr_; }

 private:
  T *ptr_;
};

int main() {
  std::unique_ptr<int> p(new int(42));
  p.release();  // 释放资源，但不删除对象
  int *raw_ptr = new int(42);
  {
    UniquePtr<int> p2(raw_ptr);
    // p2.release();  // 释放资源，但不删除对象
  }
  std::cout << " " << *raw_ptr << std::endl;
}