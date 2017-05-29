#include <iostream>
#include "gtest/gtest.h"

#include "xs/xs1024.h"

TEST(XS1024, RandomRealRange) {
  xs1024 r;
  xs1024_init(&r, 42);
  for (int i = 0; i < 1000; ++i) {
    double const x = xs1024_double(&r);
    EXPECT_TRUE(x < 1.0 && x >= 0.0);
  }
}
