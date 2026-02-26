#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>

// 生产者消费者模型
template <typename T>
class Producer_Consumer {
 public:
  void produce() {
    while (running_) {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_condition_variable.wait(lock, [this]() {
        return !running_ || m_queue.size() < m_max_size;
      });                 // 等待队列不满
      m_queue.push(T());  // 生产一个产品
      lock.unlock();
      m_condition_variable.notify_one();  // 通知消费者
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
  }

  void consume() {
    while (running_) {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_condition_variable.wait(
          lock, [this]() { return !running_ || !m_queue.empty(); });

      m_queue.pop();  // 消费一个产品
      m_condition_variable.notify_one();
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  }

  void stop() {
    running_ = false;
    m_condition_variable.notify_all();
  }

 private:
  bool running_ = true;
  std::size_t m_max_size = 5;
  std::queue<T> m_queue;
  std::mutex m_mutex;
  std::condition_variable m_condition_variable;
};

int main() {
  Producer_Consumer<int> pc;
  std::thread producer1(&Producer_Consumer<int>::produce, &pc);
  std::thread producer2(&Producer_Consumer<int>::produce, &pc);
  std::thread consumer1(&Producer_Consumer<int>::consume, &pc);
  std::thread consumer2(&Producer_Consumer<int>::consume, &pc);
  std::thread consumer3(&Producer_Consumer<int>::consume, &pc);
  producer1.join();
  producer2.join();
  consumer1.join();
  consumer2.join();
  consumer3.join();
  pc.stop();
  return 0;
}