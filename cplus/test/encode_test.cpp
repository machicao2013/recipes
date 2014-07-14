#include <iostream>
#include <string>

#include <stdio.h>
using namespace std;

int URLEncodeForSpace(const char* str, const int strSize, char* result, const int resultSize){
    int i;
    int j = 0;//for result index
    char ch;
    if ((str==NULL) || (result==NULL) || (strSize<=0) || (resultSize<=0))  {
        return 0;
    }
    for ( i=0; (i<strSize)&&(j<resultSize); ++i) {
        ch = str[i];
        if (ch == ' ' || ch == '\t') {
            if (j+3 < resultSize) {
                sprintf(result+j, "%%%02X", (unsigned char)ch);
                j += 3;
            } else {
                return 0;
            }
        } else {
            result[j++] = ch;
        }
    }
    result[j] = '\0';
    return j;
}

int main()
{
    string query_url = "http://pubnet.sandai.net:8080/20/758c345e4810e3c571f4dc250cb44d5725e8adcf/568a3fc4f8f74506f2f5291d5d0744ea2ab90cb1/5a3f0e7f/200000/0/24bc53/0/0/5a3f0e7f/0/index=0-28814/indexmd5=29bf88e39c8abe01b2a22c4932ec7260/e6d86a5876626ed8ba04034a4500c340/20b2f66d85b172e16c36b2e796dd32ba/568a3fc4f8f74506f2f5291d5d0744ea2ab90cb1_IBOdownload_.flv.xv?type=vod&movieid=175377&subid=903236&ext=.xv";
    cout << query_url << endl;
    char buf[1024] = {0};
    int encode_length = URLEncodeForSpace(query_url.c_str(), query_url.length(), buf, sizeof(buf));
    if (encode_length > 0)
    {
        cout << "===================================" << endl;
        std::string encode_url = std::string(buf, encode_length);
        if ( encode_url != query_url)
        {
            //LOG4CPLUS_DEBUG(logger, "url query need to encode: " <<tsp->m_query_url << "-->" << encode_url);
            cout << encode_url << endl;
            return 1;
        }
    }

    return 0;
}


