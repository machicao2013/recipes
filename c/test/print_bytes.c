#include <stdio.h>

void print_bytes(char *bytes, int length, int line_count)
{
    int i = 1;
    for(; i <= length; ++i) {
        printf("%02x\t", *(bytes + i - 1));
        if(line_count != 0 && i % line_count == 0) {
            printf("\n");
        }
    }
}

