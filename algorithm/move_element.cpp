#include <iostream>
#include <iterator>
using namespace std;

// 将数组中的元素等于某个值的移到最右边
// description:
//  1. 找到下标为i的元素，使得array[i] == -1
//  2. 找到下标为j的元素，使得array[j] != -1,并且j > i
//  3. swap(array[i], array[j])
//  4. i++, j++
//  5. 重复2

typedef bool (*Fun)(int);

int move_element(int *array, uint32_t size, Fun fn)
{
    uint32_t i = 0 , j = 0;/*{{{*/
    uint32_t count = size;
    while (i < size && !fn(array[i])) {
        i++;
    }
    if (i == size) {
        return count;
    } else {
        count--;
    }
    j = i;
    do {
        j += 1;
        while (j < size && fn(array[j])) {
            count--;
            j++;
        }
        if (j == size) {
            break;
        }
        std::swap(array[i], array[j]);
        i++;
    } while ((i < size) && (j < size));
    return count;/*}}}*/
}

int move_element_2(int *array, uint32_t size, Fun fn)
{
    int *result = array;
    int *first = array;
    int *last = array + size;

    while (first != last) {
        if (!fn(*first) && first != result) {
            // *result = *first;
            std::swap(*result, *first);
            result++;
        }
        first++;
    }
    return (result - array);
}

bool equal_minus_1(int data)
{
    return (data == -1);
}

int main(int argc, const char *argv[])
{
    int array[] = {1, 2, 3, -1, 4, 5, -1};
    cout << "original array: ";
    copy(array, array + sizeof(array)/sizeof(array[0]), ostream_iterator<int>(cout, "\t"));
    cout << endl;
    // cout << move_element(array, sizeof(array)/sizeof(array[0]), equal_minus_1) << endl;
    // for (int32_t i = 0; i < sizeof(array)/sizeof(array[0]); i++) {
        // cout << array[i] << "\t";
    // }
    // cout << endl;

    cout << move_element_2(array, sizeof(array)/sizeof(array[0]), equal_minus_1) << endl;
    for (int32_t i = 0; i < sizeof(array)/sizeof(array[0]); i++) {
        cout << array[i] << "\t";
    }
    cout << endl;
    return 0;
}
