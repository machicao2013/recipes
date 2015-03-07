1. TCP不会自动检测连接是否丢失.
2. 只有在向已终止的对等实体进行第二次写操作时，应用程序才会收到通知。因为第一次写操作会重置连接，而在这个过程中所有数据都丢失。
3. TCP使用两种算法防止拥塞。两种方法都用到了另一个被称为拥塞窗口(congestion window)的窗口控制拥塞。TCP在任意时刻能够发送的最大数据量是发送和拥塞窗口中的最小值。这两个窗口负责的是流量控制的不同方面。发送窗口由对等实体TCP控制，防止我们发送的数据使对等实体的缓冲区溢出。拥塞窗口由我们的TCP控制，防止我们发送超出网络容量的数据。将数据传输量限制在这两个窗口的最小值之内，就可以保证实现这两种类型的流量控制了.
    - 方法一：慢启动：慢慢地将向网络发送数据的速率增加到一个门限值。在慢启动阶段，拥塞窗口的大小呈指数增长。
    - 方法二：拥塞避免：当拥塞窗口的长度达到被称为慢启动门限(slow start threshold)的门限值，慢启动阶段就结束了，由另一个拥塞避免(congestion avoidance)算法接管。在拥塞避免过程中，假设连接已进入稳定状态，并不断刺探网络以发现变成可用状态的额外带宽。在拥塞避免阶段，拥塞窗口是线性开放的--每个往返时间内最多开放一个段。
4. 对TCP发送策略来说，拥塞窗口可能会隐含的阻止原来可能允许发送的数据。如果(丢失的分段说明)出现了拥塞，拥塞窗口就会减小，可能会减小到一个段长。根据排队数据的多少以及应用程序试图发送数据的多少，可能会阻止部分或全部数据的传送。
5. 影响TCP发送策略的另外一个因素是Nagle算法。算法指出，在任意指定时刻，未被确认的小段不能超过一个。这里小段指的是长度小于MSS的段。Nagle算法的目的是防止TCP用一系列的小段来充斥网络。TCP会将数量较少的数据保存起来，知道收到对前一个小段的ACK为止，然后将所有数据一次性地发送出去。
6. shutdown:如果关闭连接的接收端，则套接字无法接收更多的数据，如果应用程序再进行读操作，都会返回EOF。如果连接关闭后，unix会刷新输入队列，丢弃应用程序还未读取的所有数据。如果有新数据到达，TCP会进行ACK，然后悄悄地将其丢弃，因为应用程序再也无法接收数据了。
7. shutdown:如果关闭连接的发送端，将套接字标识为无法发送任何额外的数据，后继所有试图对套接字进行的写操作都会出错。将发送缓冲区中所有的数据都发送出去之后，TCP会向其对等实体发送一个FIN，通知它还没有其它数据了。这被称为半关闭(half close)。
8. 使用TIME-WAIT状态的目的：
    - 维护连接状态，以防主动关闭连接的那端发送的最后一条ACK丢失后造成另一端重新发送FIN信号;
    - 为耗尽网络中所有此连接的走失段提供时间
9. SO_LINGER选项：struct linger {int l_onoff; int l_linger};如果成员l_onoff为0，linger选项就被关闭，其行为与默认行为相同--close或closesocket调用立即返回，内核继续尝试发送所有未发送的数据。如果l_onoff非零，其行为就取决于l_linger的值。如果l_linger非零，就将其作为内核等待挂起的数据被发送出去并被确认时逗留的时间间隔。也就是说，close或closesocket在所有数据都发送完毕，或者时间间隔到期之前是不会返回的。如果逗留定时器到期时，仍然有未发送的数据，close或closesocket就返回EWOULDBLOCK，所有未发送数据都可能丢失。如果数据发送出去了，这两个调用就返回0.如果成员l_linger为0，就将连接丢弃。也就是说，向对等实体发送一个RST，不经过TIME-WAIT状态就立即关闭连接。
10. 在Unix下，连接建立起来时，套接字就成为可写的了。如果出错，套接字会成为既可读又可写。但是不能根据这个来查看连接是否成功，因为在调用select之前，connect就可能成功，并有数据可以读取了。在这种情况下，套接字可能是既可读又可写，就像出错了一样。作为替代方案，我们调用了getsockopt，以便从套接字中解析出错误状态。见下面的代码(非阻塞套接字判断connect是否成功)
    int isconnected(int socket, fd_set *rd, fd_set *wr, fd_set *ex)
    {
        int err;
        int len = sizeof(err);
        errno = 0;
        // 既不可读，也不可写，说明连接没有建立
        if( !FD_ISSET(s, rd) && !FD_ISSET(s, wr))
            return 0;
        if( getsockopt(s, SOL_SOCKET, SO_ERROR, &err, &len ) < 0)
            return 0;
        errno = err;
        return (errno == 0);
    }

    int conn_nonb(int sockfd, const struct sockaddr_in *saptr, socklen_t salen, int nsec)
    {
        int flags, n, error, code;
        socklen_t len;
        fd_set wset;
        struct timeval tval;

        flags = fcntl(sockfd, F_GETFL, 0);
        fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

        error = 0;
        if ((n == connect(sockfd, saptr, salen)) == 0) {
            goto done;
        } else if (n < 0 && errno != EINPROGRESS) {
            return (-1);
        }

        /* Do whatever we want while the connect is taking place */

        FD_ZERO(&wset);
        FD_SET(sockfd, &wset);
        tval.tv_sec = nsec;
        tval.tv_usec = 0;

        if ((n = select(sockfd+1, NULL, &wset, NULL, nsec ? &tval : NULL)) == 0) {
            close(sockfd);  /* timeout */
            errno = ETIMEDOUT;
            return (-1);
        }

        if (FD_ISSET(sockfd, &wset)) {
            len = sizeof(error);
            code = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len);
            /* 如果发生错误，Solaris实现的getsockopt返回-1，
             * 把pending error设置给errno. Berkeley实现的
             * getsockopt返回0, pending error返回给error.
             * 我们需要处理这两种情况 */
            if (code < 0 || error) {
                close(sockfd);
                if (error)
                    errno = error;
                return (-1);
            }
        } else {
            fprintf(stderr, "select error: sockfd not set");
            exit(0);
        }
    done:
        fcntl(sockfd, F_SETFL, flags);  /* restore file status flags */
        return (0);
    }
11. 建议：将发送缓冲区的长度至少应该设置为MSS的3倍大。























