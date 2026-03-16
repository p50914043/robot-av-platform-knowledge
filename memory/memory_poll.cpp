#include <cstddef>
#include <cstdlib>
#include <iostream>

// 内存块设计：用联合体 FreeBlock 实现空间复用 —— 空闲时存储指向下一个空闲块的指针，使用时存储用户数据。
// 内存池初始化：构造函数中一次性申请一大块连续内存，将其分割为多个固定大小的块，并用链表串联所有空闲块。
// 内存分配：从空闲链表头部取出一个块，更新链表头。
// 内存释放：将释放的块重新挂回空闲链表头部。
// 资源回收：析构函数中释放预先申请的大块内存。

template <typename T>
class MemoryPool {
 private:
  union FreeBlock {
    FreeBlock* next;
    alignas(T) char data[sizeof(T)];  // 强制data成员按T的自然对齐方式对齐
  };

  char* pool_start_;
  size_t block_size_;
  size_t total_blocks_;
  FreeBlock* free_list_;

 public:
  // 构造函数：初始化内存池，指定预分配的内存数量
  explicit MemoryPool(size_t chunk_size = 1024)
      : block_size_(sizeof(FreeBlock)), total_blocks_(chunk_size), free_list_(nullptr) {
    // 一次性申请大块连续内存
    pool_start_ = new char[chunk_size * block_size_];

    // 将每块串起来，初始化空闲链表
    for (size_t i = 0; i < chunk_size; ++i) {
      FreeBlock* block = reinterpret_cast<FreeBlock*>(pool_start_ + i * block_size_);
      block->next = (i == chunk_size - 1) ? nullptr : reinterpret_cast<FreeBlock*>(pool_start_ + (i + 1) * block_size_);
    }
    // 指定第一个空闲块为链表头
    free_list_ = reinterpret_cast<FreeBlock*>(pool_start_);
  }

  ~MemoryPool() {
    delete[] pool_start_;  // 释放大块内存
  }

  MemoryPool(const MemoryPool&) = delete;
  MemoryPool& operator=(const MemoryPool&) = delete;
  MemoryPool(MemoryPool&&) = delete;
  MemoryPool& operator=(MemoryPool&&) = delete;

  T* allocate() {
    if (free_list_ == nullptr) {
      throw std::bad_alloc();
    }

    FreeBlock* block = free_list_;
    free_list_ = block->next;

    return reinterpret_cast<T*>(block);
  }

  void deallocate(T* ptr) {
    if (ptr == nullptr)
      return;
    FreeBlock* block = reinterpret_cast<FreeBlock*>(ptr);
    block->next = free_list_;
    free_list_ = block;
  }

  size_t free_blocks() const {
    size_t count = 0;
    for (FreeBlock* block = free_list_; block != nullptr; block = block->next) {
      ++count;
    }
    return count;
  }
};

int main() {
  MemoryPool<int> pool;
  int* p1 = pool.allocate();

  for (auto i = 0, j = 0; i < 4 && j < 4; i++, j++) {
    std::cout << "free_blocks: " << pool.free_blocks() << std::endl;
  }

  for (auto i = 0; i < 1024; i++) auto p2 = pool.allocate();
  return 0;
}
