#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
// 单线程线程池
class SingleThreadPool {
 public:
  SingleThreadPool() {
    thread_ = std::thread(std::bind(&SingleThreadPool::Run, this));
  }

  ~SingleThreadPool() {
    {
      std::lock_guard<std::mutex> lock(mutex_);
      is_stop_ = true;
      std::cout << "thread pool stop" << std::endl;
    }
    cond_.notify_one();
    thread_.join();
  }

  void AddTask(const std::function<void()> &task) {
    {
      std::lock_guard<std::mutex> lock(mutex_);
      task_queue_.push(task);
      std::cout << "task " << task_queue_.size() << " is added" << std::endl;
    }

    cond_.notify_one();
  }

  void Run() {
    while (true) {
      std::unique_lock<std::mutex> lock(mutex_);
      std::cout << "thread pool wait for task" << std::endl;

      cond_.wait(lock, [this] {
        return !task_queue_.empty() || is_stop_;
      });  // 等待任务到来
      if (is_stop_) {
        break;
      }
      std::cout << "thread pool run" << std::endl;
      while (!task_queue_.empty()) {
        auto task = task_queue_.front();
        task_queue_.pop();
        lock.unlock();
        task();
        lock.lock();
      }
    }
  }

 private:
  std::thread thread_;
  std::mutex mutex_;
  std::condition_variable cond_;
  bool is_stop_ = false;
  std::queue<std::function<void()>> task_queue_;
};

// 多线程线程池
class MultiThreadPool {
 public:
  MultiThreadPool(int thread_num) {
    for (int i = 0; i < thread_num; ++i) {
      threads_.emplace_back(
          std::thread(std::bind(&MultiThreadPool::Run, this)));
    }
  }

  ~MultiThreadPool() {
    {
      std::lock_guard<std::mutex> lock(mutex_);
      is_stop_ = true;
    }
    cond_.notify_all();
    for (auto &thread : threads_) {
      thread.join();
    }
  }

  void AddTask(const std::function<void()> &task) {
    {
      std::lock_guard<std::mutex> lock(mutex_);
      task_queue_.push(task);
      std::cout << "task " << task_queue_.size() << " is added" << std::endl;
    }
    cond_.notify_one();
  }

  void Run() {
    while (true) {
      std::unique_lock<std::mutex> lock(mutex_);
      cond_.wait(lock, [this] { return !task_queue_.empty() || is_stop_; });
      if (is_stop_) {
        break;
      }
      auto task = task_queue_.front();
      task_queue_.pop();
      lock.unlock();
      task();
      lock.lock();
    }
  }

 private:
  std::vector<std::thread> threads_;
  std::mutex mutex_;
  std::condition_variable cond_;
  std::queue<std::function<void()>> task_queue_;
  bool is_stop_ = false;
};

int main() {
  // 单元测试代码

  SingleThreadPool pool;
  for (int i = 0; i < 10; ++i) {
    pool.AddTask(
        [i] { std::cout << "task " << i << " is running" << std::endl; });
  }

  MultiThreadPool pool2(2);
  for (int i = 0; i < 10; ++i) {
    pool2.AddTask(
        [i] { std::cout << "task " << i << " is running" << std::endl; });
  }

  std::this_thread::sleep_for(std::chrono::seconds(5));
  return 0;
}