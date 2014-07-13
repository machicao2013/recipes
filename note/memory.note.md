# basic knowledge
1. SRAM比DRAM快，但是成本高
2. SRAM现在应用在CPU的高速缓存和芯片
3. 除了CPU外，系统中还有其它的一些组件也可以访问主存。高性能网卡或大规模控制器是无法承受通过CPU来传输数据的，他们一般直接对内存进行读写(直接内存访问,DMA).它们可以通过南桥和北桥直接访问内存。
4. instead of putting the SRAM under the control of the OS or user, it becomes a resource which is transparently used and administered by the processors. In this mode, SRAM is used to make temporary copies of(to cache, in other words) data in main memory which is likely to be used soon by the processor.This is possible because program code and data has temporal and spatial locality.
5. Realizing that locality exists is key to the concept of CPU caches as we use them today.
6. the data flow in reality need not pass through any of the higher-level caches on the way from the core to the main memory.(实际上，从CPU core到主存的数据流不需要经过任何高级别的缓存)
7. the entries stored in the caches are not single words but, instead, "lines" of several contiguous words. In early caches these lines were 32 bytes long; nowadays the norm is 64 bytes.(缓存不是以字节为单位，而是以缓存行为单位)
8. cache line指在慢速的off-chip dram和快速的on-chip cpu cache间数据传输的最小单位. 
9. A cache line which has been written to and which has not been written back to main memory is said to be "dirty". Once it is written the dirty flag is cleared.
10. In symmetric multi-processor(SMP) systems the caches of the CPUs cannot work independently from each other. All processors are supposed to see the same memory content at all times. The maintenance of this uniform view of memory is called "cache coherency". If a processor were to look simply at its own caches and main memory it would not see the content of dirty cache lines in other processors.
11. Providing direct access to the caches of one processor from another processor would be terribly expensive and a huge bottleneck. Instead, processors detect when another processor wants to read or write to a certai cache line.
12. a few simple rules:
    - A dirty cache line is not present in any other processor's cache(一个脏的缓存行不会在任何其他的处理器缓存中存在)
    - Clean copies of the same cache line can reside in arbitrarily many caches.(一个缓存行的干净副本可以存在于多个缓存中)

# Cache coherency Implementation
## Cache policies:

- ** write-through cache Implementation **
> If the cache line is written to, the processor immediately also writes the cache line into main memory.This ensures that, at all times, the main memory and cache are in sync. The cache content could simply be discarded whenever a cache line is replaced. This cache policy is simple but not very fast.
- ** write-back cache Implementation **
>The write-back policy is more sophisticated. Here the processor does not immediately write the modified cache line back to main memory. Instead, the cache line is only marked as dirty. When the cache line is dropped from the cache at some point in the future the dirty bit will instruct the processor to write the data back at that time instead of just discarding the content. most memory in a system with a decent processor is cached this way.
>
>But there is a significant problem with the write-back Implementation. When more than one processor(or core or hyper-thread) is available and accessing the same memory it must still be assured(确保) that both processor see the same memory content at all times. If a cache line is dirty on one processor(i.e., it has not been written back yet) and a second processor tries to read the same memory location, the read operation cannot just go out to the main memory. Instead the content of the first processor's cache line is needed.
>
>It is completely impractical to provide direct access from one processor to the cache of another processor. The connection is simply not fast enough, for a start. The practical alternative is to transfer the cache content over to the other processor in case it is needed.(当另外一个处理器需要时，传输缓存内容到这个处理器). Note that this also applies to caches which are not shared on the same processor.

- ** write-combining **
>write-combining combines multiple write accesses before the cache line is written out.

- ** uncacheable **
>this usually means the memory location is not backed by RAM at all. it might be a special address which is hardcoded to have some functionality implemented outside the CPU.

##Multi-Processor Support
1. ** 接着上面的2).**
>The question now is when does this cache line transfer have to happen? This question is pretty easy to answer: when one processor needs a cache line which is dirty in another processor's cache for reading or writing. But how can a Processor determine whether a cache line is dirty in another Processor's cache? Assuing it just because a cache line is loaded by another processor would be suboptimal (at best). Usually the majority of memory accesses are read accesses and the resulting cache lines are not dirty. Processor operations on cache lines are frequent which means broadcasting information about changed cache lines after each write access would be impractical.(问题是缓存行的传输是什么时候发生的？这个问题很容易回答：当处理器A需要缓存C,而C被另一个处理器B标记为dirty时，不管是对于read还是write。 但是处理器A是怎么知道缓存C被处理器B标志为dirty的呢？假设仅仅是因为处理器B加载了C,只是一种次优的方案。 对于内存的访问，大部份是读操作， 这样的话缓存就不会被标志为dirty。而且处理器操作缓存是非常频繁的，这意味着在每一次写操作之后广播缓存行改变的信息是不切实际的)

2. ** use MESI(modified, exclusive, shared, invalid) cache coherency protocol to solve this problem.**
>** Modified **: the local processor has modified the cache line. This also implies it is the only copy in any cache.
>
>** Exclusive(独有的) **: The cache line is not modified but known to not be loaded into any other processor's cache
>
>** Shared **: The cache line is not modified and might exist in another processor's cache
>
>** Invalid **: The cache line is invalid, i.e., unused
3. With these four states it is possible to efficiently implement write-back caches while also supporting concurrent use of read-only data on different processors.
4. A thread is migrated from one processor to another and all the cache lines have to be moved over to the new processor once.
5. What should be clear is that if the two hyper-threads execute completely different code the cache size is indeed cut in half which means a significant increase in cache misses. Such OS scheduling practices are questionable unless the caches are sufficiently large.
5. What should be clear is that if the two hyper-threads execute completely different code the cache size is indeed cut in half which means a significant increase in cache misses. Such OS scheduling practices are questionable unless the caches are sufficiently large.
5. What should be clear is that if the two hyper-threads execute completely different code the cache size is indeed cut in half which means a significant increase in cache misses. Such OS scheduling practices are questionable unless the caches are sufficiently large.
5. What should be clear is that if the two hyper-threads execute completely different code the cache size is indeed cut in half which means a significant increase in cache misses. Such OS scheduling practices are questionable unless the caches are sufficiently large.
5. What should be clear is that if the two hyper-threads execute completely different code the cache size is indeed cut in half which means a significant increase in cache misses. Such OS scheduling practices are questionable unless the caches are sufficiently large.
## Other Details
###. So far we talked about the address as consisting of three parts, tag, set index, and cache line offset. But what address is actually used?
1. The problem with virtual addresses is that they are not unique.
2. The virtual addresses used during execution which must to be translated with the help of the Memory Management Unit(MMU) into physical address. (在执行期，虚拟地址必须被MMU转成物理地址). This is a non-trivial(耗时的) operation. In the pipeline(流水线) to execute an instruction the physical address might only be available at a later stage.(在使用流水线执行指令的过程中，物理地址可能会在下一个stage才能获得)
3. Processor designers are currently using ** virtual address ** tagging for the ** first ** level caches.(处理器的设计者会在一级缓存中使用虚拟地址). These caches are rather small and can be cleared without too much pain. At least partial clearing the cache is necessary if the page table tree of a process changes. It might be possible to avoid a complete flush if the processor has an instruction which allows to specify the virtual address range which has changed. ** Given the low latency of L1i and L1d caches(~3 cycles) using virtual addresses is almost mandatory(强制的) **
4. ** For larger caches including L2, L3,... caches physical address tagging is needed. ** These caches have a higher latency and the virtual-> physical address translation can finish in time.(这些缓存有高延迟，从虚拟地址到物理地址的转换可以消除这部分时间) Because these caches are larger(i.e, a lot of information is lost when they are flushed) and refilling them takes a long time due to the main memory access latency, flushing them often would be costly.
### Instruction Cache ###
1. CPUs have been designed with ** pipelines **. That means the execution of an instruction happens in stages. First an instruction is decoded, then the parameters are prepared, and finally it is executed. Such a pipeline can be quite long(> 20 stages for Intel's Netburst architecture).
2. In recent years these processors therefore do not cache the raw byte sequence of the instructions in L1i but instread they cache the decoded instructions.
3. the caches from L2 on are unified(统一的) caches which contain both code and data. Obviously here the code is cached in the byte sequence form and not decoded.
4. Core微体系结构(酷睿)的一级缓存与二级缓存都采用Write back的存储方式，以64字节为存储单位。而Netburst微体系结构(Pentium4)的一级缓存采用Write Through的存储方式，以64字节位存储单位，二级缓存采用Write Back的存储方式，以128字节为存储单位。
### Cache Placement ###
1. Hyper-threads, by definition share everything but the register set. This includes the L1 caches.
## Virtual Memory ##
1. The virtual memory subsystem of a processor implements the virtual address spaces provided to each process.
2. A virtual address is implemented by the Memory Management Unit(MMU) of the CPU. The OS has to fill out the page table data structures, but most CPUs do the rest of the work themselves.
3. All the data structures for the page tables are kept in the main memory; this is where the OS constructs and updates the tables. Upon creation of a process or a change of a page table the CPU is notified.
4. The pabe tables are used to resolve every virtual address into a physical address using the page table walk described above.
5. Instead of just caching the directory table entries, the complete computation of the address of the physical page is cached.(not including the page offset part of the virtual address). The cache into which the computed values are stored is called the Translation Look_Aside Buffer(TLB). It is usually a small cache since it has to be extremely fast.
6. Modern CPUs provide multi-level TLB caches, just as for the other caches; the higher-level caches are larger and slower.
7. The TLB is a processor-core global resource. ** All threads and processes executed on the processor core use the same TLB. ** Since the translation of virtual to physical addresses depends on which page table tree is installed, the CPU cannot blindly(盲目地) reuse the cached entries if the page table is changed. ** Each process has a different page table tree(but not the threads in the same process) ** as does the kernel and the VMM if present.
## NUMA Support ##
1. In the simplest form of NUMA, a processor can have local memory which is cheapter to access than memory local to other processors.
2. ** The problem of many processors access the same memory. ** For commodity hardware all processors would share the same Northbridge. This make the Northbridge a server bottleneck since all memory traffic is routed through it.
3. The OS should not migrate a process or thread from one node to another. The OS should already try to avoid migrating processes on normal multi-processor machines because migrating from one processor to another means the cache content is lost. If load distribution requires migrating a process or thread off of a processor, the OS can ususally pick an arbitrary new processor which has sufficient capacity left.
4. By default, not allocated exclusively on the local node.(默认情况下，内存不仅仅是分配在本地的node上)。
### Published Information ###
1. The kernel publishes, through the sys pseudo file system(sysfs), information about the processor caches below ** /sys/devices/system/cpu*/cache **.
2. The ** sys ** file system exposes topology information in the files below ** /sys/devices/system/cpu/cpu*/topology **
3. For each process the kernel provides a pseudo-file /proc/PID/numa_maps, where PID is the ID of the process. The important information in the file is the values for N0 to N3, which ** indicate the number of pages allocated for the memory area on nodes 0 to 3. **
4. Programmers wishing to improve their programs' performance will find it best to focus on changes affected the level 1 cache since those will likely yield the best results.
5. The theme for all memory access is the same: imporve locality(spatial and temporal) and align the code and data.
6. The processor automatically prefetches data when memory is accessed sequentially.
## Atomicity Optimization ##
1. CAS(compare and swap)
    CAS(addr, expval, newval)
    {
        if(*addr == expval)
        {
            *addr = newval;
            return true;
        }
        return false;
    }
2.
