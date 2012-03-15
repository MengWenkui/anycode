#include <stdio.h>
#include "gtest/gtest.h"

int add(int a, int b)
{
  return a + b;
}

float addf(float a, float b)
{
  return a + b;
}

class AddTest: public testing::Test
{
public:
  static void SetUpTestCase()
  {
    printf("test begin\n");
  }
  static void TearDownTestCase()
  {
    printf("test end\n");
  }

  AddTest()
  {
    printf("Test C\n");
  }
  ~AddTest()
  {
    printf("Test D\n");
  }
};

TEST_F(AddTest, add_int)
{
  EXPECT_EQ(10, add(5, 5));
  EXPECT_NE(10, add(5, 6));
}

TEST_F(AddTest, add_float)
{
  EXPECT_EQ(5.5, addf(2.25, 3.25));
  EXPECT_NE(5.5, addf(2.25, 4.25));
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
