#include "../src/hello.h"
#include <gtest/gtest.h>

TEST(HelloTest, Basic)
{
    EXPECT_EQ(add(2, 3), 5);
}