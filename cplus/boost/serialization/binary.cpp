#include "SDCondValue.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <string>
#include <vector>

#include <hiredis/hiredis.h>

void print_bytes(const char *bytes, int length, int line_count)
{
    int i = 1;
    for(; i <= length; ++i) {
        if (isprint(bytes[i])) {
            printf("%c", bytes[i]);
        }else{
            printf("\\x%02x", *(bytes + i - 1));
        }
        if(line_count != 0 && i % line_count == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

int hgetall(redisContext *m_redis_context, const std::string &key, std::vector<Value> &values)
{
    uint32_t size = 0;
    const char *argv[size + 2];
    size_t argvlen[size + 2];
    // command
    std::string command = "HGETALL";
    argv[0] = command.c_str();
    argvlen[0] = command.length();
    // key
    argv[1] = key.data();
    argvlen[1] = key.length();
    printf("key len: %zd\n", argvlen[1]);
    print_bytes(argv[1], argvlen[1], 5000);
    redisReply *reply = (redisReply *)redisCommandArgv(m_redis_context, size + 2, argv, argvlen);
    if(!reply) {
        //Once an error is returned the context cannot be reused and you should set up a new connection
        printf("%s\n", "hgetall error");
        //close();
        return -1;
    }
    //LOG4CPLUS_DEBUG(logger, "redisCommand " << command << " succ, reply type:" << reply->type);
    if(reply->type != REDIS_REPLY_ARRAY) {
        //LOG4CPLUS_ERROR(logger,"HMGET key:" << key << " reply type:" << reply->type << "fileds:" << size << "/" << reply->elements);
        printf("%s\n", "return value type error");
        freeReplyObject(reply);
        return 0;
    }
    uint32_t has_data = 0,idx=0;
    uint32_t num = reply->elements;
    printf("========%u\n", num);
    std::string filed,value;
    for(idx = 0; idx < num; idx += 2) {
        redisReply *value_replay_filed = reply->element[idx],*value_replay_value= reply->element[idx+1];
        filed = std::string(value_replay_filed->str,value_replay_filed->len);
        value = std::string(value_replay_value->str,value_replay_value->len);
        Value tmp(filed,value,0);
        values.push_back(tmp);
        ++has_data;
    }
    //LOG4CPLUS_DEBUG(logger, "redisCommand " << command << " succ ,reply fileds size:" << reply->elements << ", has_date:" << has_data);
    freeReplyObject(reply);
    return has_data > 0 ? 1 : 0;
}

void saveData(std::string data)
{
    unsigned int j;
    redisContext *c;
    redisReply *reply;
    const char *hostname = "127.0.0.1";
    //int port = 6381;
    int port = 6379;

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    /* select database*/
    reply = (redisReply *)redisCommand(c, "SELECT 1");
    printf("SELECT 1: %s\n", reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(c, "SET %s %b", "hello", data.data(), data.size());
    printf("SET 1: %s\n", reply->str);
    freeReplyObject(reply);

    //std::vector<Value> values;
    //hgetall(c, data, values);

    /* Disconnects and frees the context */
    redisFree(c);
}

int main()
{
    //string key="http://wt.bkill.com:806/1303/EWFxtbhgj.bkill.com.zip";
    std::string key="http://drivers1_2011.drivethelife.com/1/A9/06/HP_hdc_9.2.0.1015_None_27152.7zgbk";
    std::vector<Condition> conds;
    conds.push_back(Condition("U", key, 0));
    RedisKey rediskey(1,conds);
    stringstream binay_stream;
    boost::archive::binary_oarchive binary_oa(binay_stream);
    binary_oa << (rediskey);
    key = binay_stream.str();
    saveData(key);
    print_bytes(key.data(), key.size(), 1000);
    printf("\n");
    return 0;
}
