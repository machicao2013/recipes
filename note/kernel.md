# kenel parameter #
1. 操作系统支持打开的最大文件描述符的个数：/proc/sys/fs/file-nr /proc/sys/fs/file-max,编辑文件/etc/sysctl.conf
    fs.file-max = 1020000
    net.ipv4.ip_conntrack_max = 1020000
    net.ipv4.netfilter.ip_conntrack_max = 1020000
2. 每个进程能够打开的最大文件描述符的个数：ulimit -n,要永久修改，则编辑/etc/security/limits.conf,加入如下行：
    work         hard    nofile      1020000
    work         soft    nofile      1020000
3. 网络相关的内核参数：
    net.ipv4.tcp_rmem = 8192 87380 16777216
    net.ipv4.tcp_wmem = 8192 65536 16777216
    net.ipv4.tcp_mem = 8388608 12582912 16777216
    net.core.rmem_default = 262144
    net.core.wmem_default = 262144
    net.core.rmem_max = 16777216
    net.core.wmem_max = 16777216
    net.ipv4.tcp_moderate_rcvbuf = 1
    net.ipv4.tcp_adv_win_scale = 2
4. 缓存上限是什么：SO_SNDBUF和SO_RCVBUF都是用来设置缓存上线的，都是个体化的设置，即，只会影响到设置过的连接，而不会对其它连接生效。SO_SNDBUF表示这个连接上的内核写缓存上限。实际上是SO_SNDBUF*2，当设置了SO_SNDBUF时，就相当于划定了所操作的TCP连接上的写缓存能够使用的最大内存。然而，这个值也不是可以由着进程随意设置的，它会受制于系统级的上下限，当它大于上面的系统配置wmem_max（net.core.wmem_max）时，将会被wmem_max替代（同样翻一倍）；而当它特别小时，例如在2.6.18内核中设计的写缓存最小值为2K字节，此时也会被直接替代为2KSO_RCVBUF表示连接上的读缓存上限，与SO_SNDBUF类似，它也受制于rmem_max配置项，实际在内核中也是2倍大小作为读缓存的使用上限。SO_RCVBUF设置时也有下限，同样在2.6.18内核中若这个值小于256字节就会被256所替代。
5. 缓存的大小与TCP的滑动窗口到底有什么关系？读缓存的作用有2个：1、将无序的、落在接收滑动窗口内的TCP报文缓存起来；2、当有序的、可以供应用程序读取的报文出现时，由于应用程序的读取是延时的，所以会把待应用程序读取的报文也保存在读缓存中。所以，读缓存一分为二，一部分缓存无序报文，一部分缓存待延时读取的有序报文。这两部分缓存大小之和由于受制于同一个上限值，所以它们是会互相影响的，当应用程序读取速率过慢时，这块过大的应用缓存将会影响到套接字缓存，使接收滑动窗口缩小，从而通知连接的对端降低发送速度，避免无谓的网络传输。当应用程序长时间不读取数据，造成应用缓存将套接字缓存挤压到没空间，那么连接对端会收到接收窗口为0的通知，告诉对方：我现在消化不了更多的报文了。在以太网里，MSS大小为1460，此时初始窗口大小为4倍的MSS.将1500字节的MTU去除了20字节的IP头、20字节的TCP头以后，一个最大报文能够承载的有效数据长度。但有些网络中，会在TCP的可选头部里，使用12字节作为时间戳使用，这样，有效数据就是MSS再减去12，初始窗口就是（1460-12）*4=5792，这与窗口想表达的含义是一致的，即：我能够处理的有效数据长度。当窗口从初始窗口一路扩张到最大接收窗口时，最大接收窗口就是最大读缓存吗？不是，因为必须分一部分缓存用于应用程序的延时报文读取。到底会分多少出来呢？这是可配的系统选项，如下：net.ipv4.tcp_adv_win_scale = 2 .这里的tcp_adv_win_scale意味着，将要拿出1/(2^tcp_adv_win_scale)缓存出来做应用缓存。即，默认tcp_adv_win_scale配置为2时，就是拿出至少1/4的内存用于应用读缓存，那么，最大的接收滑动窗口的大小只能到达读缓存的3/4。
6. linux的TCP缓存上限自动调整策略:引入了自动调整内存分配的功能，由tcp_moderate_rcvbuf配置决定: net.ipv4.tcp_moderate_rcvbuf = 1 ,当我们在编程中对连接设置了SO_SNDBUF、SO_RCVBUF，将会使linux内核不再对这样的连接执行自动调整功能！6. linux的TCP缓存上限自动调整策略:引入了自动调整内存分配的功能，由tcp_moderate_rcvbuf配置决定: net.ipv4.tcp_moderate_rcvbuf = 1 ,当我们在编程中对连接设置了SO_SNDBUF、SO_RCVBUF，将会使linux内核不再对这样的连接执行自动调整功能！6. linux的TCP缓存上限自动调整策略:引入了自动调整内存分配的功能，由tcp_moderate_rcvbuf配置决定: net.ipv4.tcp_moderate_rcvbuf = 1 ,当我们在编程中对连接设置了SO_SNDBUF、SO_RCVBUF，将会使linux内核不再对这样的连接执行自动调整功能！6. linux的TCP缓存上限自动调整策略:引入了自动调整内存分配的功能，由tcp_moderate_rcvbuf配置决定: net.ipv4.tcp_moderate_rcvbuf = 1 ,当我们在编程中对连接设置了SO_SNDBUF、SO_RCVBUF，将会使linux内核不再对这样的连接执行自动调整功能！6. linux的TCP缓存上限自动调整策略:引入了自动调整内存分配的功能，由tcp_moderate_rcvbuf配置决定: net.ipv4.tcp_moderate_rcvbuf = 1 ,当我们在编程中对连接设置了SO_SNDBUF、SO_RCVBUF，将会使linux内核不再对这样的连接执行自动调整功能！6. linux的TCP缓存上限自动调整策略:引入了自动调整内存分配的功能，由tcp_moderate_rcvbuf配置决定: net.ipv4.tcp_moderate_rcvbuf = 1 ,当我们在编程中对连接设置了SO_SNDBUF、SO_RCVBUF，将会使linux内核不再对这样的连接执行自动调整功能！
7. 系统最大的进程号：/proc/sys/kernel/pid_max
# reference #
    - [1](http://www.ideawu.net/blog/archives/740.html)
    - [2](http://blog.csdn.net/russell_tao/article/details/18711023)
