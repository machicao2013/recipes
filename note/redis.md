# Introduction to Redis #
1. Redis is an open source, BSD licensed, advanced ** key-value store **. It is often referred to as a ** data structure server ** since keys can contain ** strings **, ** hashes **, ** lists **, ** sets ** and ** sorted sets **.
2. You can run ** atomic operation ** on these types, like ** appending to a string**; ** incrementing the value in a hash **; ** pushing to a list**; ** computing set intersection, union ** and ** difference **; or ** getting the member with highest ranking in a sorted set**.
3. In order to achieve its outstanding performance, Redis works with an ** in-memory dataset **. Depending on your use case, you can persist it either by ** dumping the dataset to disk ** every once in a while, or by ** appending each command to a log**.
4. Redis also supports trivial-to-setup ** master-slave replication **. with very fast non-blocking first synchronization, auto-reconnection on net split and so forth.
5. Other features include ** Transactions, Pub/Sub, Lua scripting, Keys with a limited time-to-live **, and configuration settings to make Redis behave like a cache.
6. redis是一种NoSQL数据库,对于CAP理论，其主要关注C和A.
7. Redis事务保证了一致性和隔离性，但是不保证原子性和持久性。

# When to Use Redis #
## Using SQL or NoSQL to store your data ##
1. //TODO
2. One thing to keep in mind is that NoSQL databases generally don't provide ACID(Atomicity, consistency, isolation, durability), or do it only partially. This allows them to make a few tradeoffs that wouldn't be possible otherwise.
3. Redis provides partial ACID compliance by design due to the fact that it is single threaded(which guarantees consistency and isolation), and full compliance if confiured with ** appendfsync always **, providing durability as well.
4. Performance can also be a key factor. NoSQL databases are generally faster, partially for write operations, making them a good fit for applications that are write-heavy.
5. Picking between SQL(for stable, predictable, relational data) and NoSQL(for temporary, highly dynamic data).
6. **Redis is extremely fast, making it perfectly suited for applications that are write-heavy, data that changes often, and data that naturally fits one of Redis's data structures(for instance, analysics data). A scenario where you probably shouldn't use Redis is if you have a very large dataset of which only a small part is "host"(accessed often) or a case where your dataset doesn't fit in memory. **
7. Mysql负责处理它擅长的关系型存储，而NoSQL负责数据的储存.提高MySQl Query Cache缓存命中率。我们知道query cache缓存失效是表级的，在MySQL表一旦被更新就会失效，经过这种字段的分离，更新的字段如果不是存储在MySQL中，那么对query cache就没有任何影响。而NoSQL的Cache往往都是行级别的，只对更新的记录的缓存失效。
8. 在一些数据库结构经常变化，数据结构不定的系统中，就非常适合使用NoSQL来存储
# Leveraging Redis #
1. Using Redis as a Key/Value Store.
# Leveraging Redis #
1. Using Redis as a Key/Value Store.
# Leveraging Redis #
1. Using Redis as a Key/Value Store.
2. Redis positions itself not simply as a key value store but as a server for data structure as well. This means that on top of typical key/value store functionality, it gives you several ways to store and manipulate application data.
# Configuring Persistence #
1. The default persistence model is snapshotting, which consists of saving the entire database to disk in the RDB format (basically a compressed database dump). This can be done periodically at set times, or every time a configurable number of keys changes.
2. The alternative is using an ** Append Only File(AOF) **. This might be a better option if you have a large dataset or your data doesn't change very frequently.

# Redis Cluster #
1. redis是一个单线程io复用的结构，无法有效利用服务器的多核结构，如果能在一台多核机器起多个redis进程，共同提供服务，效率会更高一些。
2. failover机制(失效备份机制)：通俗地说，即当A无法为客户服务时，系统能够自动地切换，使B能够及时地顶上继续为客户提供服务，且客户感觉不到这个为他提供服务的对象已经更换。
3. 乐观锁:大多数是基于数据版本(version)的记录机制实现的。何谓数据版本?即为数据增加一个版本标识,在基于数据库表的版本解决方案中,一般是通过为数据库表添加一个“version”字段来实现读取出数据时,将此版本号一同读出,之后更新时,对此版本号加 1。此时,将提交数据的版本号与数据库表对应记录的当前版本号进行比对,如果提交的数据版本号大于数据库表当前版本号,则予以更新,否则认为是过期数据。


# Redis Transactions #
1. 第一个问题是 redis 只能保证事务的每个命令连续执行,但是如果事务中的一个命令失败了,并不回滚其他命令,比如使用的命令类型不匹配。
2. Redis Cluster is ** not able to guarantee strong consistency**. In practical terms this means that under certain conditions it is possible that Redis Cluster will forget a write that was acknowledged by the system.

# Redis Persistence #
1. redis支持两种持久化方式，一种是Snapshotting,也是默认的方式，另一种是Append-only file的方式。
2. client 也可以使用 save 或者 bgsave 命令通知 redis 做一次快照持久化。save 操作是在主线程中保存快照的,由于 redis 是用一个主线程来处理所有 client 的请求,这种方式会阻塞所有client 请求。所以不推荐使用。另一点需要注意的是,每次快照持久化都是将内存数据完整写入到磁盘一次,并不是增量的只同步变更数据。如果数据量大的话,而且写操作比较多,必然会引起大量的磁盘 io 操作,可能会严重影响性能。
3. 在一定间隔时间做一次的,所以如果 redis 意外 down 掉的话,就会丢失最后一次快照后的所有修改。如果应用要求不能丢失任何修改的话,可以采用aof持久化方式。

# Redis的局限性 #
1. Redis的主要缺点是数据库容量受到物理内存的限制，不能用作海量数据的高性能读写，并且它没有原生的可扩展机制，不具有scale（可扩展）能力，要依赖客户端来实现分布式读写，因此Redis适合的场景主要局限在较小数据量的高性能操作和运算上

[reference]
1. [reference1](http://blog.sina.com.cn/s/blog_693f08470101klls.html)

