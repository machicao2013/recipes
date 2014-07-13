// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include <cstdio>
#include <iostream>
#include "kv.h"
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <server/TThreadedServer.h>
#include <server/TThreadPoolServer.h>
#include <server/TNonblockingServer.h>
#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>



#include <leveldb/db.h>
#include <leveldb/cache.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;


using boost::shared_ptr;

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

class kvHandler : virtual public kvIf {
	public:
		kvHandler(const std::string& dbName) : 
			dbName_(dbName) 
		{
			// Your initialization goes here

			// open all the existing databases
			leveldb::Options options;
			options.create_if_missing = true;
			options.error_if_exists = false;
			options.write_buffer_size = 500 * 1048576; // 500MB write buffer
			options.block_cache = leveldb::NewLRUCache(1500 * 1048576);  // 1.5GB cache

			leveldb::Status status = leveldb::DB::Open(options, dbName, &db_);
			if (!status.ok()) std::cerr << status.ToString() << std::endl;

			assert(status.ok());
		}

		ResponseCode::type ping() {
			// Your implementation goes here
			DEBUG_LOG("ping");
			return ResponseCode::Success;
		}

		ResponseCode::type put(const std::string& key, const std::string& value) {
			// Your implementation goes here
			DEBUG_LOG("put %s", key.c_str());

			leveldb::WriteOptions options;
			options.sync = false;
			leveldb::Status status = db_->Put(options, key, value);

			if (!status.ok()) {
				return ResponseCode::Error;
			}
			return ResponseCode::Success;
		}

		void get(RecordResponse& _return, const std::string& key) {
			// Your implementation goes here
			DEBUG_LOG("get %s", key.c_str());
			//1. get cookie_id list
			leveldb::Status status = db_->Get(leveldb::ReadOptions(), key, &(_return.value));
			if (status.IsNotFound()) {
				_return.responseCode = ResponseCode::KeyNotFound;
				return;
			} else if (!status.ok()) {
				_return.responseCode = ResponseCode::Error;
				return;
			}

			//2. get cookie log
			_return.responseCode = ResponseCode::Success;
		}

		ResponseCode::type remove(const std::string& key) {
			// Your implementation goes here
			DEBUG_LOG("remove %s", key.c_str());

			leveldb::WriteOptions options;
			options.sync = false;
			leveldb::Status status = db_->Delete(options, key);
			if (status.IsNotFound()) {
				return ResponseCode::KeyNotFound;
			} else if (!status.ok()) {
				return ResponseCode::Error;
			}
			return ResponseCode::Success;
		}

	private:
		std::string dbName_; // directory to store db files.
		leveldb::DB* db_;
};

int main(int argc, char **argv) {
	int port = 9090;
	shared_ptr<kvHandler> handler(new kvHandler("db_test"));
	shared_ptr<TProcessor> processor(new kvProcessor(handler));
	shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

	int thread_num = 4;
	shared_ptr<ThreadManager> threadManager;
	
	if(thread_num>1)
	{
		// using thread pool with thread_num threads to handle incoming requests
		threadManager =
			ThreadManager::newSimpleThreadManager(thread_num);
		shared_ptr<PosixThreadFactory> threadFactory =
			shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
		threadManager->threadFactory(threadFactory);
		threadManager->start();
	}

	TNonblockingServer server(processor, protocolFactory, port, threadManager);
	server.serve();

	return 0;
}
