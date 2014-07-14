#include <gtest/gtest.h>

TEST(CommonSuit, mod)
{
    // 求模后的符号和data相同
    int data = 25;
    int mod_data = 4;
    ASSERT_EQ(1, data % mod_data);
    mod_data = -4;
    ASSERT_EQ(1, data % mod_data);
    data = -25;
    mod_data = 4;
    ASSERT_EQ(-1, data % mod_data);
    mod_data = -4;
    ASSERT_EQ(-1, data % mod_data);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
