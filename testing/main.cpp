#include <iostream>
#include <cassert>
#include "../TestClass.h"

#include "catch.hpp"

TEST_CASE("test") {
  foo(42);
  foo(23);

  TestClass<double> t(1.0);
  TestClass<double> t_2;
  t.foo();

  const TestClass<double>& t_const = t;

  REQUIRE(t.get_val() == 1.0);
  REQUIRE(t_const.get_val() == 1.0);

  t.val() = 2.0;
  REQUIRE(t.get_val() == 2.0);
  REQUIRE(t_const.get_val() == 2.0);

  t.set_val(4.0);
  const auto val = t_const.val();

  REQUIRE(t.get_val() == 4.0);
  REQUIRE(val == 4.0);
}
