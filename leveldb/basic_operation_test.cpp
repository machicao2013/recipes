#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <leveldb/db.h>
#include <leveldb/options.h>
#include <leveldb/write_batch.h>
#include <leveldb/slice.h>
using namespace std;

TEST(LeveldbOperation, TestOpenDB)
{
    // open db
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    // options.error_if_exists = true;
    leveldb::Status status = leveldb::DB::Open(options, "./testdb.db", &db);
    EXPECT_TRUE(status.ok());
    if (!status.ok()) {
        cout << "******" << status.ToString() << endl;
    }
    // closing db
    delete db;
}

TEST(LeveldbOperation, TestReadWrite)
{
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "./testdb.db", &db);
    ASSERT_TRUE(status.ok());
    std::string key = "name";
    std::string value = "xiaoming";
    status = db->Put(leveldb::WriteOptions(), key, value);
    EXPECT_TRUE(status.ok());
    value = "";
    if (status.ok()) {
        status = db->Get(leveldb::ReadOptions(), key, &value);
        EXPECT_TRUE(status.ok());
        EXPECT_STREQ("xiaoming", value.c_str());
    }
    // closing db
    delete db;
}

TEST(LeveldbOperation, TestAtomicUpdate)
{
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "./testdb.db", &db);
    ASSERT_TRUE(status.ok());

    std::string key1 = "name";
    std::string key2 = "first name";
    std::string value;
    status = db->Get(leveldb::ReadOptions(), key1, &value);
    EXPECT_TRUE(status.ok());
    leveldb::WriteBatch batch;
    batch.Delete(key1);
    batch.Put(key2, value);
    status = db->Write(leveldb::WriteOptions(), &batch);
    ASSERT_TRUE(status.ok());
    delete db;
}

TEST(LeveldbOperation, TestIterator)
{
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "./testdb.db", &db);
    ASSERT_TRUE(status.ok());

    leveldb::Iterator *itr = db->NewIterator(leveldb::ReadOptions());
    for(itr->SeekToFirst(); itr->Valid(); itr->Next()) {
        cout << itr->key().ToString() << ":" << itr->value().ToString() << endl;
    }
    delete itr;

    delete db;
}

TEST(LeveldbOperation, TestSnapshot)
{
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "./testdb.db", &db);
    ASSERT_TRUE(status.ok());

    leveldb::ReadOptions read_options;
    read_options.snapshot = db->GetSnapshot();
    leveldb::Iterator *itr = db->NewIterator(read_options);
    for(itr->SeekToLast(); itr->Valid(); itr->Prev()) {
        cout << itr->key().ToString() << ":" << itr->value().ToString() << endl;
    }
    delete itr;

    db->ReleaseSnapshot(read_options.snapshot);

    delete db;
}

static void print(const leveldb::Slice &slice)
{
    cout << slice.ToString() << endl;
}

TEST(LeveldbOperation, TestSlice)
{
    leveldb::Slice slice1 = "hello";
    // have bug, str outof range
    if(!slice1.empty()) {
        std::string str = "world";
        slice1 = str;
    }
    print(slice1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
