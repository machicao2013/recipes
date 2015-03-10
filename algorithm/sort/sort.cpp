#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// http://student.zjzk.cn/course_ware/data_structure/web/paixu/paixu8.4.2.2.htm
//
static void quick_sort_core(int *array, size_t begin, size_t end);
static size_t partition(int *array, size_t begin, size_t end);

void quick_sort(int *array, size_t count)
{
    if (array == NULL || count == 0 || count == 1) {
        return;
    }
    quick_sort_core(array, 0, count-1);
}

static void quick_sort_core(int *array, size_t begin, size_t end)
{
    if (begin >= end) {
        return;
    }
    size_t pos = partition(array, begin, end);
    if (pos == 0) {
        quick_sort_core(array, pos + 1, end);
    } else if(pos == end) {
        quick_sort_core(array, begin, pos - 1);
    } else {
        quick_sort_core(array, begin, pos - 1);
        quick_sort_core(array, pos + 1, end);
    }
}

static size_t partition(int *array, size_t begin, size_t end)
{
    int temp = array[begin];
    while (begin < end) {
        while (begin < end && temp <= array[end]) {
            end--;
        }
        if (begin < end) {
            array[begin] = array[end];
            //begin++;
        }
        while (begin < end && temp >= array[begin]) {
            begin++;
        }
        if (begin < end) {
            array[end] = array[begin];
            //end--;
        }
    }
    array[begin] = temp;
    return begin;
}

static void heap_down(int *array, size_t pos, size_t end)
{
    int temp = array[pos];
    size_t lchild = 2 * pos + 1;
    while (lchild <= end) {
        if (lchild < end && array[lchild + 1] > array[lchild]) {
            lchild = lchild + 1;
        }
        if (array[pos] > array[lchild]) {
            break;
        }
        array[pos] = array[lchild];
        pos = lchild;
        lchild = 2 * pos + 1;
    }
    array[pos] = temp;
}

void make_heap(int *array, size_t count)
{
    if (array == NULL || count <= 1) {
        return;
    }
    for (int i = (count-1)/2; i >= 0; --i) {
        heap_down(array, i, count - 1);
    }
}

void bubble_sort(int *array, size_t count)
{
    if (array == NULL || count <= 1) {
        return;
    }

    size_t i,j;
    bool flag = false;
    for (i = 1; i < count; i++) {
        flag = false;
        for (j = 0; j < count - i; j++) {
            if (array[j] > array[j+1]) {
                std::swap(array[j], array[j+1]);
                flag = true;
            }
        }
        if (!flag) {
            return;
        }
    }
}

bool check_result(int *array, size_t count)
{
     for (size_t i = 0; i < count - 1; i++) {
         if (array[i] > array[i+1]) {
             return false;
         }
     }
     return true;
}

int main()
{
    const size_t size = 1000;
    int array[size];
    srand(time(NULL));
    for (size_t i = 0; i < size; i++) {
        array[i] = rand();
    }
    //quick_sort(array, size);
    bubble_sort(array, size);
    if (!check_result(array, size)) {
        cout << "sort algorithm is wrong" << endl;
    } else {
        cout << "sort algorithm is right" << endl;
    }
    return 0;
}

