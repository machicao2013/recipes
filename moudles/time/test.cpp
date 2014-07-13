#include <gtest/gtest.h>
#include <iostream>

#include "Date.h"

using namespace std;

//Test Suite
class DateTest : public testing::Test
{
protected:
    static void SetUpTestCase()
    {
        date = new Date();
    }

    static void TearDownTestCase()
    {
        delete date;
        date = NULL;
    }

    // Some expensive resource shared by all tests.
    static Date *date;
};

Date* DateTest::date = NULL;

TEST_F(DateTest, Test1)
{
    EXPECT_TRUE(date != NULL);
    int days = date->getJulianDayNumber(2014, 6, 29);
    cout << days << endl;
    cout << date->toIsoString() << endl;
}

TEST_F(DateTest, Test2)
{
    Date _date(2014, 6, 29);
    cout << _date.julianDayNumber() << endl;
    EXPECT_STREQ("2014-06-29", _date.toIsoString().c_str());

    Date _date2(1900, 1, 1);
    cout << _date2.julianDayNumber() << endl;
    EXPECT_STREQ("1900-01-01", _date2.toIsoString().c_str());
}

int main(int argc, char **argv)
{
    // testing::AddGlobalTestEnvironment(new FooEnvironment);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
