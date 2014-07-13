#ifndef _TEST_H_
#define _TEST_H_

class Test
{
private:
    static int member;
public:
    Test();
    ~Test();
    static int getNumber();
};

//int Test::member = 0;
#endif /* end of include guard: _TEST_H_ */
