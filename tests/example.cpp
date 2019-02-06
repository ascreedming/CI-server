#include "gtest/gtest.h"

// TEST(Test, Name) { ... code ... )


long square(long n)
{
    return n * n;
}


TEST(PowerTest, SmallPositiveNumber)
{
    EXPECT_EQ(square(5), 25);
}

TEST(PowerTest, BigPositiveNumber)
{
    EXPECT_EQ(square(35000), 1225000000);
}

TEST(PowerTest, SmallNegativeNumber)
{
    EXPECT_EQ(square(-5), 25);
}

TEST(PowerTest, BigNegativeNumber)
{
    EXPECT_EQ(square(-35000), 1225000000);
}
