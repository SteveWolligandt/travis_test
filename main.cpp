#include <iostream>
#include "TestClass.h"

int main() {
  const int i = 23;
  if (i == 42)
    std::cout << "the answer to all\n";

  TestClass<double> t(1.0);
  std::cout << t.val() << '\n';
  t.val() = 2.0;
  std::cout << t.val() << '\n';
  t.set_val(4.0);
  std::cout << t.val() << '\n';
}