#ifndef _REDISCLIENT_H_
#define _REDISCLIENT_H_

#include <string>
#include <stdint.h>
#include <hiredis/hiredis.h>

#include "SDLogger.h"

class RedisClient
{
private:
    redisContext *m_context;
    std::string m_host;
    uint16_t m_port;
    uint16_t m_db;
public:
    RedisClient(const std::string &host = "127.0.0.1", uint16_t port = 6379, uint16_t db = 0);
    ~RedisClient();
    bool init();
    void close();

// connection operation
public:
    bool ping();
    bool echo(const std::string &msg);
    bool select_db(uint16_t db);


// strings operation
public:
    /// @brief get
    ///
    /// @param key
    /// @param value
    ///
    /// @return if not system err, return true, if key not exists, value=""
    bool get(const std::string &key, std::string &value);

    bool set(const std::string &key, const std::string &value, uint32_t expire = 0);
    bool strlen(const std::string &key, long long &length);
    bool incr(const std::string &key, long long &new_value);
    bool incr_by(const std::string &key, const int step, long long &new_value);
    bool decr(const std::string &key, long long &new_value);
    bool decr_by(const std::string &key, const int step, long long &new_value);
// set operation
private:

    /**
     * @param operation: one of {sdiff, sinter, sunion}
     */
    bool set_operation(const std::string &operation, const std::vector<std::string> &keys, std::vector<std::string> &values);
public:
    bool sadd(const std::string &key, const std::string &value);
    bool sadd(const std::string &key, const std::vector<std::string> &values);
    bool scard(const std::string &key, long long &count);
    bool sismember(const std::string &key, const std::string &member, bool &retval);
    bool smembers(const std::string &key, std::vector<std::string> &values);
    bool spop(const std::string &key, std::string &value);
    bool srandmember(const std::string &key, const uint32_t count, std::vector<std::string> &values);
    bool srem(const std::string &key, const std::string &member, size_t &rem_number);
    bool srem(const std::string &key, const std::vector<std::string> &members, size_t &rem_number);
    bool sdiff(const std::string &key1, const std::string &key2, std::vector<std::string> &values);
    bool sinter(const std::string &key1, const std::string &key2, std::vector<std::string> &values);
    bool sunion(const std::string &key1, const std::string &key2, std::vector<std::string> &values);
protected:
    DECL_LOGGER(logger);
};

#endif /* end of include guard: _REDISCLIENT_H_ */
