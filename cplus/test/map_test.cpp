#include <map>
#include <iostream>
using namespace std;

struct Rectangle
{
    int width;
    int height;
};

bool operator<(const Rectangle& lhs, const Rectangle& rhs)
{
    cout << "====================================" << endl;
    cout << "lhs[" << lhs.width << "," << lhs.height << "]" << "\t" << "rhs[" << rhs.width << "," << rhs.height << "]" << endl;
    return lhs.width < rhs.width;
}

int main()
{
    map<Rectangle, bool> rectangles;
    for (size_t i = 0; i < 10; i++) {
        Rectangle rectangle;
        rectangle.width = (int)i;
        rectangle.height = (int)i;
        rectangles[rectangle] = true;
    }
    map<Rectangle, bool>::iterator itr = rectangles.begin();
    for (; itr != rectangles.end(); ++itr) {
        cout << itr->second << endl;
    }

    Rectangle rectangle;
    rectangle.width = 5;
    rectangle.height = 20;
    cout << "====================================" << endl;
    itr = rectangles.find(rectangle);
    // if (itr != rectangles.end()) {
        // cout << (itr->first).width << "\t" << (itr->first).height << "\t" << itr->second << endl;
    // }

    return 0;
}
