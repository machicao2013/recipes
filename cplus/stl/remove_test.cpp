#include <iostream>

typedef bool (*Fun)(int n);

bool equal_99(int n)
{
    return (n == 99);
}

int* remove(int *begin, int *end, Fun fun = equal_99)
{
    while (begin < end) {
        while ((begin < end) && (!(*fun)(*begin))) {
            begin++;
        }

        while ((begin < end) && (*fun)(*end)) {
            --end;
        }
        if (begin < end) {
            *begin = *end;
            begin++;
            end--;
        }
    }
    return end;
}
