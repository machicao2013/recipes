/*
 * =====================================================================================
 *
 *       Filename:  kv_client_ping.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/19/2011 04:08:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  WangYao (fisherman), wangyao02@baidu.com
 *        Company:  Baidu.com, Inc
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>

#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>

#include "kv.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace boost;
using namespace kv;

#ifndef USE_DEBUG
#define DEBUG_LOG(format, args...)
#else
#define DEBUG_LOG(format, args...) \
        do{\
                        char tmpstr[65536];\
                        snprintf(tmpstr,65535,format,##args);\
                        printf("[thread:%u] %s\n", pthread_self(), tmpstr); \
        }while(0)
#endif

int main(int argc, char **argv) {
    shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
    shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    //shared_ptr<TTransport> transport(new TFramedTransport(socket));
    shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    kvClient client(protocol);

    try {
        transport->open();

        int count = 10000;
        if(argc==2)
            count = atoi(argv[1]);

		struct timeval tv_start, tv_end;
		gettimeofday(&tv_start, NULL);
        for(int i=0; i<count; i++)
        {
            char key[16] = {0};
            char value[1024] = {0};
			ResponseCode::type ret0;

            snprintf(key, sizeof(key), "%d", i);
            snprintf(value, sizeof(value), "%d", i);
            ret0 = client.ping();
        }
		gettimeofday(&tv_end, NULL);

		float seconds = (tv_end.tv_sec-tv_start.tv_sec) + (tv_end.tv_usec - tv_start.tv_usec)/1000000;
		printf("speed: %.2f count: %d, time: %.2f\n", count/seconds, count, seconds);

		transport->close();
	} catch (TException &tx) {
		printf("ERROR: %s\n", tx.what());
	}

	return 0;
}
