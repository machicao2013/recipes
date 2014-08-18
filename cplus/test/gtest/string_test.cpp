#include <gtest/gtest.h>
#include <string>
#include <arpa/inet.h>
#include "SDBase64Code.h"
using namespace std;

string get_host_of_url(const  string & url)
{
    const string PROTOCOL_SUFFIX = "://";/*{{{*/
    const string HOST_SUFFIX = "/";
    const string USRPASS_SUFFIX = "@";
    const string PORT_SUFFIX = ":";

    string host;
    string::size_type host_start, host_end;

    // host_start = url.find_first_of(PROTOCOL_SUFFIX);
    host_start = url.find(PROTOCOL_SUFFIX);
    if (host_start != string::npos ) {
        host_end = url.find_first_of(HOST_SUFFIX, host_start+PROTOCOL_SUFFIX.length());
        // cout << "=====================  Debug begin =======================" << endl;
        // cout << "host_start: " << host_start << ", host_end: " << host_end << ", url_len: " << url.length() << endl;
        // cout << "=====================  Debug end   =======================" << endl;
        if (host_end != string::npos) {
            host_start += PROTOCOL_SUFFIX.length();
            host = url.substr(host_start, host_end-host_start);
        } else {
            host = url.substr(host_start+PROTOCOL_SUFFIX.length());
        }

        // rip auth and port
        if ((host_start=host.find_first_of(USRPASS_SUFFIX)) == string::npos) {
            host_start = 0;
        } else {
            host_start += USRPASS_SUFFIX.length();
        }
        if ((host_end=host.find_last_of(PORT_SUFFIX)) == string::npos) {
            host_end = host.length();
        }

        if (host_start!=0  || host_end!=host.length()) {
            host = host.substr(host_start, host_end-host_start);
        }
    }

    return host;/*}}}*/
}

// protocol://hostname/path/filename.suffix?p=p4pdata
bool is_valid_p4p_url(const std::string &url)
{
    // 判断长度是否合法/*{{{*/
    if (url.empty() || url.length() > 255) {
        return false;
    }
    // 判断TAG是否存在
    const static string P_TAG1 = "?p=";
    const static string P_TAG2 = "&p=";
    string::size_type p = url.find(P_TAG1);
    if (p == string::npos || p < 1) {
        p = url.find(P_TAG2);
        if (p == string::npos || p < 1) {
            return false;
        } else {
            p += P_TAG2.length();
        }
    } else {
        p += P_TAG1.length();
    }
    // 解码TAG数据
    if (16 != (url.length() - p)) {
        return false;
    }
    char buf[64];
    if (12 != SDBase64Code::decode(buf, (char*)(url.c_str() + p))) {
        return false;
    }
    // 取出IP等数据
    char* ptr = buf;
    uint32_t ip;
    memcpy(&ip, ptr, sizeof(ip));
    // cout << ip << endl;
    ptr += sizeof(ip);

    uint32_t checksum;
    memcpy(&checksum, ptr, sizeof(checksum));
    ptr += sizeof(checksum);

    uint32_t tid;
    memcpy(&tid, ptr, sizeof(tid));
    //ptr += sizeof(tid);

    // 检验数据
    uint8_t* str = (uint8_t*)url.c_str();
    uint32_t len = p;

    uint8_t val = 0;
    uint32_t i;
    int32_t h = 0;

    for (i = 0; i < len; i++) {
        val = str[i];
        h = 31*h + val;
    }

    str = (uint8_t*)(&ip);
    len = sizeof(ip);
    for (i = 0; i < len; i++) {
        val = str[i];
        h = 31*h + val;
    }

    if ((uint32_t)abs(h) != checksum
        || (uint32_t)(checksum ^ (uint32_t)0x832F6DF1) != tid) {
        return false;
    }
    return true;/*}}}*/
}

int host_is_invalid(const char *hostp, uint32_t hostlen)
{
    int i, dot_num = 0;/*{{{*/
    if (!isalnum(hostp[0])) {
        return -1;
    }
    if (hostp[hostlen - 1] == '.') {
        return -2;
    } else if(!isalnum(hostp[hostlen - 1])) {
        return -2;
    }

    for (i = 1; i < (int)(hostlen - 1); i++) {
        if (!isalnum(hostp[i]) && hostp[i] != '.' && hostp[i] != '-' && hostp[i] != '_' && hostp[i] != ':') {
            return -3;
        }
        if (hostp[i] == '.')
            dot_num++;
    }

    if (hostlen < 5 || dot_num < 1) {
        return -4;
    }
    return 0;/*}}}*/
}

bool ip_is_valid(const string &ip)
{
    unsigned char buf[255];/*{{{*/
    bool result = true;
    if ((inet_pton(AF_INET, ip.c_str(), buf) <= 0) && (inet_pton(AF_INET6, ip.c_str(), buf) <= 0)) {
        result = false;
    }
    return result;/*}}}*/
}

std::string get_file_suffix_from_url(const std::string &url)
{
    std::string result = "";/*{{{*/
    size_t pos = url.find_last_of("/");
    // cout << "--------------------" << url << "\t" << pos << endl;
    if (pos != std::string::npos && (pos != url.size() - 1)) {
        result = url.substr(pos + 1);
        pos = result.find_last_of(".");
        // cout << "--------------------" << result << "\t" << pos << endl;
        if (pos != std::string::npos && (pos != result.size() - 1)) {
            result = result.substr(pos + 1);
        } else {
            result = "";
        }
    }
    return result;/*}}}*/
}

TEST(StringSuit, length)
{
    string data = "ma幸song";
    ASSERT_EQ(9, data.length());
}

TEST(StringSuit, is_valid_p4p_url)
{
    string url = "http://js22.ctt.cache.c10050.com:443/data4/down_temp/divide_part_4/C49A6AECC479869267E6B77F6256DC37A0A40C52.aspx?p=ekhAhoBijztxD6C4";/*{{{*/
    // string url = "http://111.161.126.50:443/data1/new_download/1/1D1581BBE6E14FC806D6B2C221FA1109895DC137?p=b6F+Mqv4325alfDt";
    EXPECT_TRUE(is_valid_p4p_url(url));
    // cout << url << endl;[>}}}<]
}

TEST(StringSuit, find_first_of)
{
    string url = "http://pubnet.sandai.net:8080/0/83B071CF0494244D2CC7EAFE96D318159F5EE365/D824913B3C44C7FD1E68260DA22BF1512DBDA1D7/1aa62a11/200000/0/4afb9/0/0/1aa62a11/fa40ad2cc00d1d888af81306f7b2d9b4/来自星星的你_第2集.mkv";/*{{{*/
    size_t pos = url.find_first_of("thunder::");
    ASSERT_EQ(0, pos);
    pos = url.find("http://pubnet.sandai.net");
    ASSERT_EQ(0, pos);
    url = "^T^VVC&鲁垄貌梅?f<96>?W?露^F`陋鹿?m鹿b娄?^Y<880>氓颅拢]莽卢卢17茅<9b><86>_bd.rmvb|165141950|AA34C65B595A859087D15FE7B06B250B|h=IJ5A3EPTBYJG6GNY2H3NV2K7MT44XYPR|/";
    // find是查找全部匹配
    pos = url.find("http://pubnet.sandai.net");
    ASSERT_EQ(string::npos, pos);
    // find_first_of是查找任意一个匹配的字符
    pos = url.find_first_of("http://pubnet.sandai.net");
    ASSERT_NE(string::npos, pos);/*}}}*/
}

TEST(StringSuit, get_host_of_url)
{
    string url = "^T^VVC&鲁垄貌梅?f<96>?W?露^F`陋鹿?m鹿b娄?^Y<880>氓颅拢]莽卢卢17茅<9b><86>_bd.rmvb|165141950|AA34C65B595A859087D15FE7B06B250B|h=IJ5A3EPTBYJG6GNY2H3NV2K7MT44XYPR|/";/*{{{*/
    string host = get_host_of_url(url);
    ASSERT_EQ("", host);/*}}}*/
}

TEST(StringSuit, host_is_invalid)
{
    string host = "127.0.0.1";/*{{{*/
    ASSERT_EQ(0, host_is_invalid(host.c_str(), host.size()));
    host = "13.123";
    // EXPECT_NE(0, host_is_invalid(host.c_str(), host.size()));/*}}}*/
}

TEST(StringSuit, ip_is_valid)
{
    string host = "127.0.0.1";/*{{{*/
    EXPECT_TRUE(ip_is_valid(host));
    host = "13.123";
    ASSERT_FALSE(ip_is_valid(host));
    host = "1234.3.2.5";
    ASSERT_FALSE(ip_is_valid(host));
    host = "::FFFF:204.152.189.116";
    ASSERT_TRUE(ip_is_valid(host));
    host = "::1";
    ASSERT_TRUE(ip_is_valid(host));
    host = "::FFFF:264.152.189.116";
    ASSERT_FALSE(ip_is_valid(host));
    host = "::GGGG:264.152.189.116";
    ASSERT_FALSE(ip_is_valid(host));
    host = "vod15.t3.lixian.vip.xunlei.com";
    ASSERT_FALSE(ip_is_valid(host));/*}}}*/
}

TEST(StringSuit, get_file_suffix_from_url)
{
    std::string url = "file:///C:/Users/maxingsong/Downloads/jeffy-vim-v2.1.zip";
    std::string result = "";
    result = get_file_suffix_from_url(url);
    EXPECT_STREQ("zip", result.c_str());
}

TEST(StringSuit, string_test)
{
    std::string url = "file:///C:/Users/maxingsong/Downloads/jeffy-vim-v2.1.zip";
    // size_t pos = url.find_last_of("i", url.size());
    // equals to
    size_t pos = url.find_last_of("i");
    // cout << "============" << pos << "\t" << url.size() << endl;
    EXPECT_EQ(54, pos);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
