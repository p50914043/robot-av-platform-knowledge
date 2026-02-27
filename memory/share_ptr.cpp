#include <iostream>
#include <memory>

//  手动实现shared_ptr类型
template <typename T>
class shared_ptr {
 public:
  shared_ptr(T *ptr) : ptr_(ptr), count_(new int(1)) {}
  shared_ptr(const shared_ptr &other) : ptr_(other.ptr_), count_(other.count_) {
    ++(*count_);
  }
  shared_ptr &operator=(const shared_ptr &other) {
    if (this != &other) {
      --(*count_);
      ptr_ = other.ptr_;
      count_ = other.count_;
      ++(*count_);
    }
    return *this;
  }
  ~shared_ptr() {
    --(*count_);
    if (*count_ == 0) {
      delete ptr_;
      delete count_;
    }
  }

  T &operator*() { return *ptr_; }

  T *operator->() { return ptr_; }

  int use_count() const { return *count_; }

 private:
  T *ptr_;
  int *count_;
};

int main() {
  shared_ptr<int> p1(new int(10));
  shared_ptr<int> p2(p1);
  std::cout << "p1.use_count(): " << p1.use_count() << std::endl;
  std::cout << "p2.use_count(): " << p2.use_count() << std::endl;
  return 0;
}
