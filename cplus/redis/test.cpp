#include <iostream>

#ifdef LOGGER
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
using namespace log4cplus;
#endif

#include "RedisClient.h"
#include <gtest/gtest.h>

using namespace std;

class RedisClientTest : public testing::Test
{
public:/*{{{*/
    static RedisClient *m_client;
protected:
    static void SetUpTestCase()
    {
        m_client = new RedisClient();
        m_client->init();
        cout << "RedisClientTest SetUpTestCase invoked" << endl;
    }
    static void TearDownTestCase()
    {
        if (NULL != m_client) {
            delete m_client;
        }
        cout << "RedisClientTest TearDownTestCase" << endl;
    }/*}}}*/
};

RedisClient* RedisClientTest::m_client = NULL;

TEST_F(RedisClientTest, ping)
{
    ASSERT_EQ(true, m_client->ping());
}

TEST_F(RedisClientTest, echo)
{
    EXPECT_TRUE(m_client->echo("hello world"));
}

TEST_F(RedisClientTest, select_db)
{
    for (uint32_t i = 0; i < 16; i++) {
        EXPECT_TRUE(m_client->select_db(i));
    }
    EXPECT_TRUE(m_client->select_db(0));
}

TEST_F(RedisClientTest, set)
{
    char buffer[10];/*{{{*/
    for (uint32_t i = 0; i < 5; i++) {
        sprintf(buffer, "hello%d", i);
        std::string key = buffer;
        sprintf(buffer, "world%d", i);
        std::string value = buffer;
        EXPECT_TRUE(m_client->set(key, value));
    }

    // for number
    sprintf(buffer, "%d", 20);
    std::string value = buffer;
    EXPECT_TRUE(m_client->set("data", value));/*}}}*/
}

TEST_F(RedisClientTest, get)
{
    char buffer[10];/*{{{*/
    for (uint32_t i = 0; i < 5; i++) {
        sprintf(buffer, "hello%d", i);
        std::string key = buffer;
        std::string value;
        EXPECT_TRUE(m_client->get(key, value));
        sprintf(buffer, "world%d", i);
        EXPECT_STREQ(buffer, value.c_str());
    }
    sprintf(buffer, "hello%d", 6);
    std::string key = buffer;
    std::string value;
    EXPECT_TRUE(m_client->get(key, value));
    EXPECT_STREQ("", value.c_str());/*}}}*/
}

TEST_F(RedisClientTest, strlen)
{
    char buffer[10];/*{{{*/
    sprintf(buffer, "hello%d", 0);
    std::string key = buffer;
    long long length = 0;
    EXPECT_TRUE(m_client->strlen(key, length));
    EXPECT_EQ(6, length);

    sprintf(buffer, "hello%d", 7);
    key = buffer;
    length = 0;
    EXPECT_TRUE(m_client->strlen(key, length));
    EXPECT_EQ(0, length);/*}}}*/
}

TEST_F(RedisClientTest, incr)
{
    char buffer[10];/*{{{*/
    sprintf(buffer, "hello%d", 0);
    std::string key = buffer;
    long long new_value = 0;
    EXPECT_FALSE(m_client->incr(key, new_value));

    EXPECT_TRUE(m_client->incr("data", new_value));
    EXPECT_EQ(21, new_value);/*}}}*/
}

TEST_F(RedisClientTest, decr)
{
    char buffer[10];/*{{{*/
    sprintf(buffer, "hello%d", 0);
    std::string key = buffer;
    long long new_value = 0;
    EXPECT_FALSE(m_client->decr(key, new_value));

    EXPECT_TRUE(m_client->decr("data", new_value));
    EXPECT_EQ(20, new_value);/*}}}*/
}

TEST_F(RedisClientTest, incr_by)
{
    char buffer[10];/*{{{*/
    sprintf(buffer, "hello%d", 0);
    std::string key = buffer;
    long long new_value = 0;
    EXPECT_FALSE(m_client->incr_by(key, 20, new_value));

    EXPECT_TRUE(m_client->incr_by("data", 20, new_value));
    EXPECT_EQ(40, new_value);/*}}}*/
}

TEST_F(RedisClientTest, decr_by)
{
    char buffer[10];/*{{{*/
    sprintf(buffer, "hello%d", 0);
    std::string key = buffer;
    long long new_value = 0;
    EXPECT_FALSE(m_client->decr_by(key, 20, new_value));

    EXPECT_TRUE(m_client->decr_by("data", 20, new_value));
    EXPECT_EQ(20, new_value);

    EXPECT_TRUE(m_client->decr_by("data", 30, new_value));
    EXPECT_EQ(-10, new_value);/*}}}*/
}

TEST_F(RedisClientTest, sadd)
{
    std::string key = "saddKey";/*{{{*/
    EXPECT_TRUE(m_client->sadd(key, "saddValue"));
    key = "SADD Key";
    EXPECT_TRUE(m_client->sadd(key, "sadd Value"));

    char buffer[10];
    size_t count = 5;
    std::vector<std::string> values;
    values.reserve(count);
    for (size_t i = 0; i < count; i++) {
        sprintf(buffer, "world%zu", i);
        values.push_back(buffer);
    }

    EXPECT_TRUE(m_client->sadd("multi key", values));

    values.clear();
    values.push_back("hello1");
    values.push_back("hello2");
    EXPECT_TRUE(m_client->sadd("set2", values));

    values.push_back("hello3");
    values.push_back("hello4");
    EXPECT_TRUE(m_client->sadd("set1", values));

    values.clear();
    values.push_back("hello2");
    values.push_back("hello3");
    EXPECT_TRUE(m_client->sadd("set3", values));/*}}}*/
}

TEST_F(RedisClientTest, scard)
{
    std::string key = "saddKey";/*{{{*/
    long long int count = 0;
    EXPECT_TRUE(m_client->scard(key, count));
    EXPECT_EQ(1, count);


    key = "saddKey0";
    count = 0;
    EXPECT_TRUE(m_client->scard(key, count));
    EXPECT_EQ(0, count);

    key = "multi key";
    count = 0;
    EXPECT_TRUE(m_client->scard(key, count));
    EXPECT_EQ(5, count);/*}}}*/
}

TEST_F(RedisClientTest, sismember)
{
    std::string key = "saddKey";/*{{{*/
    bool retval = false;
    EXPECT_TRUE(m_client->sismember(key, "saddValue", retval));
    EXPECT_TRUE(retval);

    key = "SADD1";
    EXPECT_TRUE(m_client->sismember(key, "saddValue", retval));
    EXPECT_FALSE(retval);/*}}}*/
}

TEST_F(RedisClientTest, smembers)
{
    std::vector<std::string> values;/*{{{*/

    std::string key = "saddKey";
    EXPECT_TRUE(m_client->smembers(key, values));
    EXPECT_TRUE(values.size() == 1);
    EXPECT_STREQ("saddValue", values[0].c_str());

    values.clear();
    key = "SADD Key";
    EXPECT_TRUE(m_client->smembers(key, values));
    EXPECT_TRUE(values.size() == 1);
    EXPECT_STREQ("sadd Value", values[0].c_str());

    values.clear();
    key = "not exists";
    EXPECT_TRUE(m_client->smembers(key, values));
    EXPECT_TRUE(values.size() == 0);

    key = "multi key";
    values.clear();
    EXPECT_TRUE(m_client->smembers(key, values));
    EXPECT_TRUE(values.size() == 5);
    char buffer[10];
    size_t count = values.size();
    for (size_t i = 0; i < count; i++) {
        sprintf(buffer, "world%zu", i);
        EXPECT_TRUE(values.end() != std::find(values.begin(), values.end(), buffer));
    }/*}}}*/
}

TEST_F(RedisClientTest, spop)
{
    std::string key = "saddKey";/*{{{*/
    std::string value = "";
    EXPECT_TRUE(m_client->spop(key, value));
    EXPECT_STREQ("saddValue", value.c_str());

    key = "multi key";
    EXPECT_TRUE(m_client->spop(key, value));/*}}}*/
}

TEST_F(RedisClientTest, srandmember)
{
    std::vector<std::string> values;/*{{{*/

    values.clear();
    std::string key = "SADD Key";
    EXPECT_TRUE(m_client->srandmember(key, 0, values));
    EXPECT_TRUE(values.size() == 1);
    EXPECT_STREQ("sadd Value", values[0].c_str());

    values.clear();
    key = "not exists";
    EXPECT_TRUE(m_client->srandmember(key, 0, values));
    EXPECT_TRUE(values.size() == 0);

    key = "multi key";
    values.clear();
    EXPECT_TRUE(m_client->srandmember(key, 4, values));
    EXPECT_TRUE(values.size() == 4); /*}}}*/
}

TEST_F(RedisClientTest, srem)
{
    std::vector<std::string> values;/*{{{*/
    std::string key = "";
    key = "SADD Key";
    size_t rem_number = 0;
    EXPECT_TRUE(m_client->srem(key, "sadd Value", rem_number));
    EXPECT_TRUE(rem_number == 1);

    key = "not exists";
    rem_number = 0;
    EXPECT_TRUE(m_client->srem(key, "hell", rem_number));
    EXPECT_TRUE(rem_number == 0);

    key = "multi key";
    values.clear();
    char buffer[10];
    for (size_t i = 0; i < 5; i++) {
        sprintf(buffer, "world%zu", i);
        values.push_back(buffer);
    }
    EXPECT_TRUE(m_client->srem(key, values, rem_number));
    EXPECT_TRUE(rem_number == 4);/*}}}*/
}

TEST_F(RedisClientTest, sdiff)
{
    std::vector<std::string> values;
    // two empty key
    std::string key1 = "hello1_set";
    std::string key2 = "hello2_set";
    EXPECT_TRUE(m_client->sdiff(key1, key2, values));
    EXPECT_TRUE(values.size() == 0);

    key1 = "set1";
    key2 = "set2";
    EXPECT_TRUE(m_client->sdiff(key1, key2, values));
    EXPECT_TRUE(values.size() == 2);
}

TEST_F(RedisClientTest, sinter)
{
    std::vector<std::string> values;
    std::string key1 = "set1";
    std::string key2 = "set2";
    EXPECT_TRUE(m_client->sinter(key1, key2, values));
    EXPECT_TRUE(values.size() == 2);
}

TEST_F(RedisClientTest, sunion)
{
    std::vector<std::string> values;
    std::string key1 = "set1";
    std::string key2 = "set2";
    EXPECT_TRUE(m_client->sunion(key1, key2, values));
    EXPECT_TRUE(values.size() == 4);
}

TEST_F(RedisClientTest, close)
{
    m_client->close();
}

int main(int argc, char **argv)
{
#ifdef LOGGER
    PropertyConfigurator::doConfigure("./conf/log4cplus.properties");
#endif
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
