#include <iostream>
#include <mutex>
#include <queue>
#include <vector>

// 滑动窗口最大值
// 解题方法：使用双端队列（deque）来维护当前窗口内的元素索引，保证队列中的元素单调递减。每次新元素入队时，先将队列中比新元素小的元素索引弹出，然后将新元素索引入队。当窗口满了之后，如果队头元素的索引已经不在窗口内了，就将其弹出。最后，队头元素的索引对应的值就是当前窗口的最大值。
std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
  std::deque<int> q;     // 存储下标,保证队列中的元素单调递减
  std::vector<int> ans;  // 存储结果
  for (int i = 0; i < nums.size(); i++) {
    while (!q.empty() && nums[i] >= nums[q.back()]) {
      q.pop_back();
    }
    q.push_back(i);
    if (i - q.front() >= k) {  // 窗口已满,需要移除队头元素
      q.pop_front();
    }
    if (i >= k - 1) {
      ans.push_back(nums[q.front()]);  // 队头元素即为当前窗口的最大值
    }
  }
  return ans;
}

// 循环队列
class CircularQueue {
 public:
  CircularQueue(int k) : capacity(k), front(0), rear(0), size(0) {
    data.resize(capacity);
  }

  bool enQueue(int value) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (capacity == size) {
      return false;
    }
    data[rear] = value;
    rear = (rear + 1) % capacity;
    size++;
    return true;
  }

  bool deQueue() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (size == 0) {
      return false;
    }
    front = (front + 1) % capacity;
    size--;
    return true;
  }

  int Front() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (size == 0) {
      return -1;
    }
    return data[front];
  }

  int Rear() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (size == 0) {
      return -1;
    }
    return data[(rear - 1 + capacity) % capacity];
  }

  bool isEmpty() {
    std::lock_guard<std::mutex> lock(mutex_);
    return size == 0;
  }

  bool isFull() {
    std::lock_guard<std::mutex> lock(mutex_);
    return size == capacity - 1;
  }

 private:
  std::vector<int> data;
  std::mutex mutex_;
  int capacity;
  int front;
  int rear;
  int size;
};

int main() {
  std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
  std::vector<int> ans = maxSlidingWindow(nums, 3);
  for (auto a : ans) {
    std::cout << a << " ";
  }

  CircularQueue q(3);
  for (size_t i = 0; i < 4; i++) {
    if (q.enQueue(i)) {
      std::cout << "enQueue " << i << std::endl;
    } else {
      std::cout << "enQueue " << i << " failed" << std::endl;
    }
  }

  std::cout << std::endl;
  return 0;
}