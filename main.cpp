#include <iostream>
#include "TestClass.h"

int main() {
  TestClass<double> t(1.0);
  std::cout << t.val() << '\n';
  t.val() = 2.0;
  std::cout << t.val() << '\n';
  t.set_val(4.0);
  std::cout << t.val() << '\n';
}