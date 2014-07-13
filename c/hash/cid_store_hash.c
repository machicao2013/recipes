#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    if (argc != 2 || 16 != strlen(argv[1])) {
        printf("Usage: %s peerID\n", argv[0]);
        return 1;
    }

    const unsigned int p = 16777619;
    unsigned int hash = (unsigned int)2166136261L;

    const char *str = argv[1];
    for (size_t i = 0; i < strlen(str); i++) {
        hash = (hash ^ str[i]) * p;
        hash += hash << 13;
        hash ^= hash >> 7;
        hash += hash << 3;
        hash ^= hash >> 17;
        hash += hash << 5;
    }
    hash = 0x7FFFFFFF & hash;
    printf("%u\t%d\t%d\n", hash, hash % 2520, (hash % 2520) / 140);
    return 0;
}
