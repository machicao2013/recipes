#include <stdio.h>
#include <assert.h>

// sum[i]代表包含array[i]的最大连续子序列和，则
//      sum[i+1] = max{array[i+1] + sum[i], array[i+1]} = array[i+1] + max{sum[i], 0}
//
int get_max_sub_seq(int *array, size_t size, int *begin, int *end)
{
    assert(NULL != array && size > 0);
    int best_result = array[0];
    int sum = array[0];
    size_t i = 1;
    int index = 0, begin_index = 0, end_index = 0;
    for (i = 1; i < size; i++) {
        if (sum > 0) {
            sum += array[i];
        } else {
            index = i;
            sum = array[i];
        }
        if (best_result < sum) {
            best_result = sum;
            begin_index = index;
            end_index = i;
        }
    }
    if (NULL != begin) {
        *begin = begin_index;
    }
    if (NULL != end) {
        *end = end_index;
    }
    return best_result;
}

int main(int argc, const char *argv[])
{
    // int array[] = {2, -3, -1, 5, 8, -7};
    int array[] = {-8, -3, -1, -5, -98, -7};
    size_t size = sizeof(array)/sizeof(array[0]);
    int begin = -1, end = -1;
    printf("%d\n", get_max_sub_seq(array, size, &begin, &end));
    printf("begin=%d, end=%d\n", begin, end);
    return 0;
}
