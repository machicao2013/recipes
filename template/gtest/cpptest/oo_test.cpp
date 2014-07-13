#include <iostream>
#include <gtest/gtest.h>

#include "FooCalc.h"
using namespace std;

//global event
class FooEnvironment : public testing::Environment
{
public:
    //在所有的TestSuite被调用之前调用
    virtual void SetUp()
    {
        std::cout << "Foo FooEnvironment SetUP" << std::endl;
    }

    //在所有的TestSuite被调用之后被调用
    virtual void TearDown()
    {
        std::cout << "Foo FooEnvironment TearDown" << std::endl;
    }
};

//test suit
/*
 *class FooTest : public testing::Test
 *{
 *protected:
 *    //在所有的TestCase被调用之前调用
 *    static void SetUpTestCase()
 *    {
 *        cout << "FooTest(Test Suit) SetUpTestCase" << endl;
 *        _shared_int = new int(5);
 *    }
 *
 *    //在所有的TestCase被调用之后调用
 *    static void TearDownTestCase()
 *    {
 *        cout << "FooTest(Test Suit) TearDownTestCase" << endl;
 *        delete _shared_int;
 *        _shared_int = NULL;
 *    }
 *
 *    // Some expensive resource shared by all tests.
 *    static int* _shared_int;
 *};
 */

//test case
class FooCalcTest:public testing::Test
{
//partition of test suit
protected:
    //在所有的TestCase被调用之前调用
    static void SetUpTestCase()
    {
        cout << "FooTest(Test Suit) SetUpTestCase" << endl;
        _shared_int = new int(5);
    }

    //在所有的TestCase被调用之后调用
    static void TearDownTestCase()
    {
        cout << "FooTest(Test Suit) TearDownTestCase" << endl;
        delete _shared_int;
        _shared_int = NULL;
    }

    // Some expensive resource shared by all tests.
    static int* _shared_int;
//partition of test case
protected:/*{{{*/
    //在每个TestCase被调用之前被调用
    virtual void SetUp()
    {
        cout << "FooCalc(Test Case) SetUp" << endl;
        m_foo.Init();
    }

    //在每个TestCase被调用之后被调用
    virtual void TearDown()
    {
        cout << "FooCalc(Test Case) TearDown" << endl;
        m_foo.Finalize();
    }

    //every test case has one, so when every test case invoked, FooCalc's Constructor will be invoked.
    FooCalc m_foo;/*}}}*/
};

int* FooCalcTest::_shared_int = 0;

TEST_F(FooCalcTest, AddTest)
{
    EXPECT_EQ(28, m_foo.Add(12, 16));
}

TEST_F(FooCalcTest, SubTest)
{
    EXPECT_EQ(-4, m_foo.Sub(12, 16));
}

int main(int argc, char **argv)
{
    testing::AddGlobalTestEnvironment(new FooEnvironment);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
