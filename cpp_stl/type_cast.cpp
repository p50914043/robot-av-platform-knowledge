#include <iostream>

class Base {
 public:
  Base() {
    std::cout << "Base()" << std::endl;
  }
  Base(const Base &) {
    std::cout << "Base(const Base&)" << std::endl;
  }
  Base(Base &&) {
    std::cout << "Base(Base&&)" << std::endl;
  }
  ~Base() {
    std::cout << "~Base()" << std::endl;
  }
};

class Derived : public Base {
 public:
  Derived() {
    std::cout << "Derived()" << std::endl;
  }
  Derived(const Derived &) = delete;
  Derived(Derived &&) {
    std::cout << "Derived(Derived&&)" << std::endl;
  }
  ~Derived() {
  }
  void print() {
    std::cout << "print()" << i << std::endl;
  }

 private:
  int i;
};

int main() {
  Base b;
  Derived *d = dynamic_cast<Derived *>(&b);  // 不安全

  d->print();
  Derived d1;
  Base &b1 = static_cast<Base &>(d1);
  //   b1.print();
  //   Base b1 = static_cast<Base &>(d);
  //   Base b2 = std::move(d);
  return 0;
}