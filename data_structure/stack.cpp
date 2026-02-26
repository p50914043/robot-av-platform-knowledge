#include <iostream>
#include <stack>
#include <vector>

// 有效括号
bool isValid(std::string s) {
  std::stack<char> stack;
  for (auto c : s) {
    if (c == '(' || c == '[' || c == '{') {
      stack.push(c);
    } else {
      if (stack.empty()) {
        return false;
      }
      char top = stack.top();
      stack.pop();
      if ((c == ')' && top != '(') || (c == ']' && top != '[') ||
          (c == '}' && top != '{')) {
        return false;
      }
    }
  }
  return stack.empty();
}
// 最小栈
class MinStack {
 public:
  MinStack() {}

  void push(int x) {
    if (stack.empty()) {
      stack.push(x);
      minStack.push(x);
    } else {
      stack.push(x);
      minStack.push(std::min(x, minStack.top()));
    }
  }

  void pop() {
    stack.pop();
    minStack.pop();
  }
  int top() { return stack.top(); }

  int getMin() { return minStack.top(); }

 private:
  std::stack<int> stack;
  std::stack<int> minStack;
};

// 接雨水
int trap(std::vector<int>& height) {
  int n = height.size();
  if (n <= 2) {
    return 0;
  }
  std::stack<int> stack;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    while (!stack.empty() && height[stack.top()] < height[i]) {
      int top = stack.top();
      stack.pop();
      if (stack.empty()) {
        break;
      }
      int left = stack.top();
      int h = std::min(height[i], height[left]) - height[top];
      int w = i - left - 1;
      ans += h * w;
    }
    stack.push(i);
  }
  return ans;
}

int main() {
  std::cout << "Hello, World!" << std::endl;
  return 0;
}