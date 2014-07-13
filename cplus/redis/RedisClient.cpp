#include "RedisClient.h"
#include <stdlib.h>
#include <string.h>
#include <vector>

IMPL_LOGGER(RedisClient, logger);

RedisClient::RedisClient(const std::string &host, uint16_t port, uint16_t db):
    m_host(host),m_port(port),m_db(db)
{
    LOG4CPLUS_DEBUG(logger, "Create RedisClient(" <<host << "," << port << "," << db << ")");
}

RedisClient::~RedisClient()
{
    close();
}

void RedisClient::close()
{
    if (NULL != m_context) {
        LOG4CPLUS_INFO(logger, "close redis client");
        redisFree(m_context);
    }
    m_context = NULL;
}

bool RedisClient::init()
{
    m_context = redisConnect(m_host.c_str(), m_port);/*{{{*/
    if (NULL == m_context) {
        LOG4CPLUS_WARN(logger, "connect to redis error, host=" << m_host << ",port" << m_port);
        return false;
    }
    if (m_context != NULL && m_context->err) {
        LOG4CPLUS_WARN(logger, "init error: err(" << m_context->errstr << ")");
        return false;
    }
    LOG4CPLUS_INFO(logger, "connect to redis success:host=" << m_host << ",port" << m_port);
    if (m_db != 0) {
        return select_db(m_db);
    }
    return true;/*}}}*/
}

bool RedisClient::ping()
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }
    redisReply *reply = (redisReply *)redisCommand(m_context, "PING");
    if (NULL == reply) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ",PING) failed! err:" << m_context->err << "(" << m_context->errstr << ")");
        return false;
    }
    if (reply->type == REDIS_REPLY_STATUS) {
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ", PING) success");
        freeReplyObject(reply);
        return true;
    } else {
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ", PING) failed, reply->type: " << reply->type);
        freeReplyObject(reply);
    }
    return false;/*}}}*/
}

bool RedisClient::echo(const std::string &msg)
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }
    redisReply *reply = (redisReply *)redisCommand(m_context, "echo %b", msg.c_str(), msg.length());
    if (NULL == reply) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", ECHO " << msg << ") failed! err: " << m_context->err << "(" << m_context->errstr << ")");
        return false;
    }
    if (reply->type == REDIS_REPLY_STRING) {
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ", ECHO " << msg << ") success!");
        freeReplyObject(reply);
        return true;
    }
    LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", ECHO " << msg << ") failed, reply->type: " << reply->type);
    freeReplyObject(reply);
    return false;/*}}}*/
}

bool RedisClient::select_db(uint16_t db)
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }
    redisReply *reply = (redisReply *)redisCommand(m_context, "SELECT %d", db);
    if (NULL == reply) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SELECT " << db << ") failed! err: " << m_context->err << "(" << m_context->errstr << ")");
        return false;
    }
    if (reply->type == REDIS_REPLY_STATUS) {
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ", SELECT " << db << ") success, reply is: " << std::string(reply->str, reply->len));
        freeReplyObject(reply);
        return true;
    }
    LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SELECT " << db << ") failed, reply->type: " << reply->type);
    freeReplyObject(reply);
    return false;/*}}}*/
}

bool RedisClient::get(const std::string &key, std::string &value)
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }
    redisReply *reply = (redisReply *)redisCommand(m_context, "GET %b", key.c_str(), key.length());

    // When an error occurs, the return value is NULL and the err field in the context will be set (see section on Errors).
    // Once an error is returned the context cannot be reused and you should set up a new connection.
    if (NULL == reply) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << "," << "GET " << ") failed! err:" << m_context->err << "(" << m_context->errstr <<")");
        return false;
    }

    if (reply->type == REDIS_REPLY_STRING) {
        value = std::string(reply->str, reply->len);
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << "," << "GET " << key << ") success, value(" << value << ")");
        freeReplyObject(reply);
        return true;
    } else if(reply->type == REDIS_REPLY_NIL) {
        value = "";
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << "," << "GET " << ")key(" << key << ") not exists");
        freeReplyObject(reply);
        return true;
    } else {
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << "," << "GET " << ")failed, reply type: " << reply->type);
    }
    return false;/*}}}*/
}

bool RedisClient::set(const std::string &key, const std::string &value, uint32_t expire)
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }
    redisReply *reply = NULL;
    if (expire == 0) {
        reply = (redisReply *)redisCommand(m_context, "SET %b %b", key.c_str(), key.length(), value.c_str(), value.length());
    } else {
        reply = (redisReply *)redisCommand(m_context, "SET %b %b EX %d", key.c_str(), key.length(), value.c_str(), value.length(), expire);
    }
    if (NULL == reply) {
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << "," << "SET)failed! err:" << m_context->err << "(" << m_context->errstr <<")");
        return false;
    }
    if (reply->type == REDIS_REPLY_STATUS) {
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << "," << "SET " << key << " " << value << " EX " << expire << ") success");
        freeReplyObject(reply);
        return true;
    }
    LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << "," << "SET " << key << " " << value << " EX " << expire << ") failed");
    freeReplyObject(reply);
    return false;/*}}}*/
}

bool RedisClient::strlen(const std::string &key, long long &length)
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }
    redisReply *reply = (redisReply *)redisCommand(m_context, "STRLEN %b", key.c_str(), key.length());
    if (NULL == reply) {
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ",STRLEN " << key << ")failed! err: " << m_context->err << "(" << m_context->errstr << ")");
        return false;
    }
    if (reply->type == REDIS_REPLY_INTEGER) {
        length = reply->integer;
        if (length == 0) {
            LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ",STRLEN " << key << "), key is not exists");
        } else {
            LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ",STRLEN " << key << ")success, value(" << length << ")");
        }
        freeReplyObject(reply);
        return true;
    }
    length = -1;
    return false;/*}}}*/
}

bool RedisClient::incr(const std::string &key, long long &new_value)
{
    return incr_by(key, 1, new_value);
}

bool RedisClient::incr_by(const std::string &key, const int step, long long &new_value)
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }
    redisReply *reply = (redisReply *)redisCommand(m_context, "INCRBY %b %d", key.c_str(), key.length(), step);
    if (NULL == reply) {
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ",INCRBY " << key << ")failed! err: " << m_context->err << "(" << m_context->errstr << ")");
        return false;
    }
    if (reply->type == REDIS_REPLY_INTEGER) {
        new_value = reply->integer;
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ", INCRBY " << key << " " << step << ")success!");
        freeReplyObject(reply);
        return true;
    }
    LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ", INCRBY " << key << " " << step << ")failed! reply->type:" << reply->type);
    freeReplyObject(reply);
    return false;/*}}}*/
}

bool RedisClient::decr(const std::string &key, long long &new_value)
{
    return decr_by(key, 1, new_value);
}

bool RedisClient::decr_by(const std::string &key, const int step, long long &new_value)
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }
    redisReply *reply = (redisReply *)redisCommand(m_context, "DECRBY %b %d", key.c_str(), key.length(), step);
    if (NULL == reply) {
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ",DECRBY " << key << ")failed! err: " << m_context->err << "(" << m_context->errstr << ")");
        return false;
    }
    if (reply->type == REDIS_REPLY_INTEGER) {
        new_value = reply->integer;
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ", DECRBY " << key << " " << step << ")success!");
        freeReplyObject(reply);
        return true;
    }
    LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ", DECRBY " << key << " " << step << ")failed! reply->type:" << reply->type);
    freeReplyObject(reply);
    return false;/*}}}*/
}

bool RedisClient::sadd(const std::string &key, const std::string &value)
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }
    std::vector<std::string> values;
    values.push_back(value);
    return sadd(key, values);/*}}}*/
}

bool RedisClient::sadd(const std::string &key, const std::vector<std::string> &values)
{
    // SADD key member [member]/*{{{*/
    if (NULL == m_context) {
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }

    // void *redisCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen);
    std::vector<const char *> argv(values.size() + 2);
    std::vector<size_t> argvlen(values.size() + 2);

    int j = 0;
    argv[j] = "SADD";
    argvlen[j] = ::strlen(argv[j]);
    j++;
    argv[j] = key.c_str();
    argvlen[j++] = key.size();

    for (size_t i = 0; i < values.size(); i++, j++) {
        argv[j] = values[i].c_str();
        argvlen[j] = values[i].size();
    }

    redisReply *reply = (redisReply *)redisCommandArgv(m_context, argv.size(), &(argv[0]), &(argvlen[0]));
    if (reply == NULL) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SADD " << key << ")failed! err: " << m_context->err << "(" << m_context->errstr << ")");
        return false;
    }

    if (REDIS_REPLY_INTEGER == reply->type) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SADD " << key << ")success! count: " << reply->integer);
        freeReplyObject(reply);
        return true;
    }

    if (REDIS_REPLY_ERROR == reply->type) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SADD " << key << ")error! error(: " << std::string(reply->str, reply->len) << ")");
    } else {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SADD" << key << ")error! error type(" << reply->type << ")");
    }
    freeReplyObject(reply);
    return false;/*}}}*/
}

bool RedisClient::scard(const std::string &key, long long &count)
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }

    redisReply *reply = (redisReply *)redisCommand(m_context, "SCARD %b", key.data(), key.size());
    if (NULL == reply) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SCARD " << key << ")failed! err: " << m_context->err << "(" << m_context->errstr << ")");
        return false;
    }

    if (REDIS_REPLY_INTEGER == reply->type) {
        count = reply->integer;
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SCARD " << key << ")success! result: " << reply->integer);
        freeReplyObject(reply);
        return true;
    }

    if (REDIS_REPLY_ERROR == reply->type) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SCARD " << key << ")error! error(: " << std::string(reply->str, reply->len) << ")");
    } else {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SCARD " << key << ")error! error type(" << reply->type << ")");
    }
    count = -1;
    freeReplyObject(reply);
    return false;/*}}}*/
}

bool RedisClient::sismember(const std::string &key, const std::string &member, bool &retval)
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }

    redisReply *reply = (redisReply *)redisCommand(m_context, "SISMEMBER %b %b", key.data(), key.size(), member.data(), member.size());
    if (NULL == reply) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SISMEMBER " << key << "," << member << ")failed! err: "
            << m_context->err << "(" << m_context->errstr << ")");
        return false;
    }

    if (REDIS_REPLY_INTEGER == reply->type) {
        retval = (reply->integer == 1);
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SISMEMBER " << key << "," << member << ")success! result: " << reply->integer);
        freeReplyObject(reply);
        return true;
    }

    if (REDIS_REPLY_ERROR == reply->type) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SISMEMBER " << key << "," << member
            << ")error! error(: " << std::string(reply->str, reply->len) << ")");
    } else {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SISMEMBER " << key << "," << member << ")error! error type(" << reply->type << ")");
    }
    retval = false;
    freeReplyObject(reply);
    return false;/*}}}*/
}

bool RedisClient::smembers(const std::string &key, std::vector<std::string> &values)
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }

    redisReply *reply = (redisReply *)redisCommand(m_context, "SMEMBERS %b", key.data(), key.size());
    if (NULL == reply) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SMEMBERS " << key << ")failed! err: "
            << m_context->err << "(" << m_context->errstr << ")");
        return false;
    }

    if (REDIS_REPLY_ARRAY == reply->type) {
        values.clear();
        size_t number = reply->elements;
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ", SMEMBERS " << key << ")success, number:" << number);
        values.reserve(number);
        redisReply *sub_reply = NULL;
        for (size_t i = 0; i < number; i++) {
            sub_reply = (redisReply *)(reply->element[i]);
            values.push_back(std::string(sub_reply->str, sub_reply->len));
        }
        freeReplyObject(reply);
        return true;
    }

    if (REDIS_REPLY_ERROR == reply->type) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SMEMBERS " << key << ")error! error(: " << std::string(reply->str, reply->len) << ")");
    } else {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SMEMBERS " << key << ")error! error type(" << reply->type << ")");
    }
    freeReplyObject(reply);
    return false;/*}}}*/
}

bool RedisClient::spop(const std::string &key, std::string &value)
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }

    redisReply *reply = (redisReply *)redisCommand(m_context, "SPOP %b", key.data(), key.size());
    if (NULL == reply) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SPOP " << key << ")failed! err: " << m_context->err << "(" << m_context->errstr << ")");
        return false;
    }

    if (REDIS_REPLY_STRING == reply->type) {
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ", SPOP " << key << ")success.");
        value = std::string(reply->str, reply->len);
        freeReplyObject(reply);
        return true;
    } else if(REDIS_REPLY_NIL == reply->type) {
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ", SPOP " << key << ")failed." << key << "not exists or key set is empty" );
        value = "";
        freeReplyObject(reply);
        return true;
    }

    if (REDIS_REPLY_ERROR == reply->type) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SPOP " << key << ")error! error(: " << std::string(reply->str, reply->len) << ")");
    } else {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SPOP " << key << ")error! error type(" << reply->type << ")");
    }
    freeReplyObject(reply);
    return false;/*}}}*/
}

bool RedisClient::srandmember(const std::string &key, const uint32_t count, std::vector<std::string> &values)
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }

    redisReply *reply = NULL;
    if (count == 0) {
        reply = (redisReply *)redisCommand(m_context, "SRANDMEMBER %b", key.data(), key.size());
    } else {
        reply = (redisReply *)redisCommand(m_context, "SRANDMEMBER %b %d", key.data(), key.size(), count);
    }
    if (NULL == reply) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SRANDMEMBER " << key << "," << count
            << ")failed! err: " << m_context->err << "(" << m_context->errstr << ")");
        return false;
    }

    if (REDIS_REPLY_ARRAY == reply->type) {
        values.clear();
        size_t number = reply->elements;
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ", SRANDMEMBER " << key << "," << count << ")success, number:" << number);
        values.reserve(number);
        redisReply *sub_reply = NULL;
        for (size_t i = 0; i < number; i++) {
            sub_reply = (redisReply *)(reply->element[i]);
            values.push_back(std::string(sub_reply->str, sub_reply->len));
        }
        freeReplyObject(reply);
        return true;
    } else if(REDIS_REPLY_STRING == reply->type) {
        values.clear();
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ", SRANDMEMBER " << key << "," << count << ")success, number: 1");
        values.push_back(std::string(reply->str, reply->len));
        freeReplyObject(reply);
        return true;
    } else if(REDIS_REPLY_NIL == reply->type) {
        values.clear();
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ", SRANDMEMBER " << key << "," << count << ")success, number: 0");
        freeReplyObject(reply);
        return true;
    }

    if (REDIS_REPLY_ERROR == reply->type) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SRANDMEMBER " << key << "," << count
            << ")error! error(: " << std::string(reply->str, reply->len) << ")");
    } else {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SRANDMEMBER " << key << "," << count << ")error! error type(" << reply->type << ")");
    }
    freeReplyObject(reply);
    return false;/*}}}*/
}

bool RedisClient::srem(const std::string &key, const std::string &member, size_t &rem_number)
{
    std::vector<std::string> members;
    members.push_back(member);
    return srem(key, members, rem_number);
}

bool RedisClient::srem(const std::string &key, const std::vector<std::string> &members, size_t &rem_number)
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }

    // void *redisCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen);
    std::vector<const char*> argv(members.size() + 2);
    std::vector<size_t> argvlen(members.size() + 2);

    int j = 0;
    argv[j] = "SREM";
    argvlen[j] = ::strlen(argv[j]);
    j++;
    argv[j] = key.c_str();
    argvlen[j++] = key.size();

    for(size_t i = 0; i < members.size(); ++i, ++j) {
        argv[j] = members[i].c_str();
        argvlen[j] = members[i].size();
    }

    redisReply *reply = (redisReply *)redisCommandArgv(m_context, argv.size(), &(argv[0]), &(argvlen[0]));
    if (NULL == reply) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SREM " << key << ")failed! err: " << m_context->err << "(" << m_context->errstr << ")");
        return false;
    }

    if (REDIS_REPLY_INTEGER == reply->type) {
        LOG4CPLUS_INFO(logger, "redisCommand(" << m_context << ", SREM " << key << ")success! number:" << reply->integer);
        rem_number = reply->integer;
        freeReplyObject(reply);
        return true;
    }

    if (REDIS_REPLY_ERROR == reply->type) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SREM " << key << ")error! error(: " << std::string(reply->str, reply->len) << ")");
    } else {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", SREM " << key << ")error! error type(" << reply->type << ")");
    }
    freeReplyObject(reply);
    return false;/*}}}*/
}

bool RedisClient::set_operation(const std::string &operation, const std::vector<std::string> &keys, std::vector<std::string> &values)
{
    if (NULL == m_context) {/*{{{*/
        LOG4CPLUS_WARN(logger, "m_context is NULL");
        return false;
    }

    std::vector<const char*> argv(keys.size() + 1);
    std::vector<size_t> argvlen(keys.size() + 1);

    size_t j = 0;
    argv[j] = operation.c_str();
    argvlen[j++] = operation.size();

    for (size_t i = 0; i < keys.size(); i++, j++) {
        argv[j] = keys[i].c_str();
        argvlen[j] = keys[i].size();
    }

    redisReply *reply = (redisReply *)redisCommandArgv(m_context, argv.size(), &(argv[0]), &(argvlen[0]));
    if (NULL == reply) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", \"" << operation << ")failed! err: " << m_context->err << "(" << m_context->errstr << ")");
        return false;
    }

    if (REDIS_REPLY_ARRAY == reply->type) {
        values.clear();
        size_t number = reply->elements;
        for (size_t i = 0; i < number; i++) {
            redisReply *sub_reply = (redisReply *)reply->element[i];
            values.push_back(std::string(sub_reply->str, sub_reply->len));
        }
        freeReplyObject(reply);
        return true;
    }

    if (REDIS_REPLY_ERROR == reply->type) {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", \"" << operation << "\")error! error(: " << std::string(reply->str, reply->len) << ")");
    } else {
        LOG4CPLUS_WARN(logger, "redisCommand(" << m_context << ", \"" << operation << "\")error! error type(" << reply->type << ")");
    }
    freeReplyObject(reply);
    return false;/*}}}*/
}

bool RedisClient::sdiff(const std::string &key1, const std::string &key2, std::vector<std::string> &values)
{
    std::vector<std::string> keys;
    keys.push_back(key1);
    keys.push_back(key2);
    return set_operation("SDIFF", keys, values);
}

bool RedisClient::sinter(const std::string &key1, const std::string &key2, std::vector<std::string> &values)
{
    std::vector<std::string> keys;
    keys.push_back(key1);
    keys.push_back(key2);
    return set_operation("SINTER", keys, values);
}

bool RedisClient::sunion(const std::string &key1, const std::string &key2, std::vector<std::string> &values)
{
    std::vector<std::string> keys;
    keys.push_back(key1);
    keys.push_back(key2);
    return set_operation("SUNION", keys, values);
}

