#ifndef TESTCLASS_H
#define TESTCLASS_H

template <typename T>
class TestClass {
public:
  TestClass(const T& val) : m_val(val) {}

  T&       val()       { return m_val; }
  const T& val() const { return m_val; }
  void set_val(const T val) { m_val = val; }

private:
  T m_val;
};

#endif