#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <iostream>

template <typename T>
class TestClass {
public:
  TestClass();
  explicit TestClass(const T& val);

  T        get_val() const;
  T&       val();
  const T& val() const;
  void set_val(const T val);

  void foo();
private:
  T m_val;
};

template <typename T>
TestClass<T>::TestClass()
  : m_val(0.0) {
}

template <typename T>
TestClass<T>::TestClass(const T& val)
  : m_val(val) {
}

template <typename T>
T& TestClass<T>::val() {
  return m_val;
}

template <typename T>
T TestClass<T>::get_val() const {
  return m_val;
}

template <typename T>
const T& TestClass<T>::val() const {
  return m_val;
}

template <typename T>
void TestClass<T>::set_val(const T val) {
  m_val = val;
}

template <typename T>
void TestClass<T>::foo() {
  std::cout << "bla\n";
}

void foo(const int i) {
  char *buffer = new char[1024];
  if (i == 42)
    std::cout << "the answer to all\n";
  else
    std::cout << "no answer available\n";
}

#endif