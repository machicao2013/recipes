#ifndef __SD_CONDITION_VALUE_H__
#define __SD_CONDITION_VALUE_H__

#include <sstream>
#include <string>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>

//for binay
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
//for xml
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

//for stl
#include <boost/archive/tmpdir.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/set.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>


#include <common/SDUtility.h>

using namespace std;
using namespace boost;


#define TYPE_STRING 0
#define TYPE_INT8   8
#define TYPE_INT16  16
#define TYPE_INT32  32
#define TYPE_INT64  64


#define BINARY_SERIALIZE 1
#define TEXT_SERIALIZE   2
#define XML_SERIALIZE     3


/* any query conditions(query object) can be
 *  abstracted as list of Conditios
 */
class Condition
{
public:
    string m_field;
    string m_value;
    int m_value_type;
    Condition() {
    }

    Condition(string field, string value, int value_type)
        :m_field(field),m_value(value),m_value_type(value_type) {
    }

    bool operator <  (const Condition &a) const {
        return m_field < a.m_field;
    }

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
#ifdef DEBUG_XML_SERIALIZE
        ar &BOOST_SERIALIZATION_NVP(m_field);
        ar &BOOST_SERIALIZATION_NVP(m_value);
        ar &BOOST_SERIALIZATION_NVP(m_value_type);
#else
        ar &m_field;
        ar &m_value;
        ar &m_value_type;
#endif
    }

};

/* any resutl object can be
 *  abstracted as list of Values
 */
class Value
{
public:
    static const uint8_t SERIALIZE = TEXT_SERIALIZE;

public:
    string m_field;
    string m_value;
    int m_value_type;

    Value() {};

    Value(string field, string value, int value_type)
        :m_field(field),m_value(value),m_value_type(value_type) {
    }

    bool operator <  (const Condition &a) const {
        return m_field < a.m_field;
    }


private:
    friend class boost::serialization::access;

    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive> void serialize(Archive &ar, const unsigned int version) {
#ifdef DEBUG_XML_SERIALIZE
        {
            ar & BOOST_SERIALIZATION_NVP(m_field);
            ar & BOOST_SERIALIZATION_NVP(m_value);
            ar & BOOST_SERIALIZATION_NVP(m_value_type);
        }
#else
        {
            ar &m_field;
            ar &m_value;
            ar &m_value_type;
        }
#endif
    }

};

class RedisKey
{
public:

    RedisKey() {
        m_type = 0;
    }

    RedisKey(uint32_t type,std::vector <Condition> condition):m_type(type),m_condition(condition) {
    }

    ~RedisKey() {
    }

    std::vector <Condition> m_condition;
    uint32_t m_type;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
#ifdef DEBUG_XML_SERIALIZE
        ar &BOOST_SERIALIZATION_NVP(m_type);
        ar &BOOST_SERIALIZATION_NVP(m_condition);
#else
        ar &m_type;
        ar &m_condition;
#endif
    }


};


#define ENCODE_VALUE_STR(values,field,value)\
    do {\
        values.push_back(Value(field, (value), TYPE_STRING));\
        LOG4CPLUS_DEBUG(logger,"ENCODE_VALUE_STR field:" << (field) << ", value:" << (value));\
    } while (0)


#define DECODE_VALUE_STR(value,field,data)\
    do {\
        if (field != value.m_field || value.m_value_type != TYPE_STRING) {\
            LOG4CPLUS_WARN(logger,"DECODE_VALUE_STR field:" << (field) << " is not the same or value type is wrong");\
            return false;\
        }\
        (data) = value.m_value;\
        LOG4CPLUS_DEBUG(logger,"DECODE_VALUE_STR field:" << (field) << ",data:" << data);\
    } while (0)


#define ENCODE_VALUE_INT(values,field,value)\
    do {\
        values.push_back(Value(field, std::string((char*)&(value),sizeof(value)), sizeof(value)));\
        LOG4CPLUS_DEBUG(logger,"ENCODE_VALUE_INT sizeof(value):" << sizeof(value) <<" field:" << (field) << ", value:" << (value) << "(" << SDUtility::str2hex((char*)&(value),sizeof(value)) << ")");\
    } while (0)


#define DECODE_VALUE_INT(value,field,data)\
    do {\
        if (field != value.m_field || sizeof(data) != value.m_value_type) {\
            LOG4CPLUS_WARN(logger,"DECODE_VALUE_INT field:" << (field) << " is not the same or value type is wrong");\
            return false;\
        }\
        memcpy(&data,(value).m_value.c_str(),sizeof(data));\
        LOG4CPLUS_DEBUG(logger,"DECODE_VALUE_INT field:" << (field) << ",data:" << data << "(" << SDUtility::str2hex((value).m_value.c_str(),sizeof(data)) << ")");\
    } while (0)


#endif  //  __SD_CONDITION_VALUE_H__

