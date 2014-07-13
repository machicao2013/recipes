#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned peerid_to_unint32_hash(const char *peerid)
{
    int result = 1;
    if (peerid == NULL) {
        return 0;
    }
    for (size_t i = 0; i < strlen(peerid); i++) {
        result = 31 * result + peerid[i];
    }
    return abs(result);
}

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s peerid\n", argv[0]);
        return -1;
    }

    unsigned hashVal = peerid_to_unint32_hash(argv[1]);
    printf("%u\n", hashVal);
    return 0;
}
