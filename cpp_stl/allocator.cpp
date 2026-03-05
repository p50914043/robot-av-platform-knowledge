#include <iostream>
#include <memory>  // 默认包含allocator
#include <string>

class Allocator {
 public:
  Allocator() = default;
  Allocator(const Allocator&) = delete;
  Allocator(Allocator&&) = delete;
  Allocator& operator=(const Allocator&) = delete;
  Allocator& operator=(Allocator&&) = delete;
  ~Allocator() = default;

  void* allocate(size_t size) {
    return ::operator new(size);
  }

  void deallocate(void* ptr, size_t size) {
    ::operator delete(ptr, size);
  }
};
