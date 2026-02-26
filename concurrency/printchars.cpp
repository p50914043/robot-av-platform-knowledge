#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
// 并发：交替打印字符串
std::mutex mtx_;
std::condition_variable cv_;
bool flag = true;
void Print1stString(std::string str) {
  for (char c : str) {
    std::unique_lock<std::mutex> lock(mtx_);
    cv_.wait(lock, []() { return flag; });
    std::cout << c;
    flag = !flag;
    cv_.notify_one();
  }
}

void Print2ndString(std::string str) {
  for (char c : str) {
    std::unique_lock<std::mutex> lock(mtx_);
    cv_.wait(lock, []() { return !flag; });  // 等待flag为false
    std::cout << c;
    flag = !flag;
    cv_.notify_one();
  }
}

// 生产者消费者模型

int main() {
  std::string str1 = "abcde";
  std::string str2 = "12345";
  std::thread t1(Print1stString, str1);
  std::thread t2(Print2ndString, str2);
  t1.join();
  t2.join();
  return 1;
}