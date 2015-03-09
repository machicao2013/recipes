#include <stdio.h>

struct str {
    int len;
    char s[0];
};

struct foo {
    struct str *a;
};

struct test{
    int i;
    short c;
    char *p;
    char s[10];
};

void test1() {
    struct test *pt=NULL;
    printf("&s = %x\n", pt->s); //等价于 printf("%x\n", &(pt->s) );
    printf("&i = %x\n", &pt->i); //因为操作符优先级，我没有写成&(pt->i)
    printf("&c = %x\n", &pt->c);
    printf("&p = %x\n", &pt->p);
}

void test2() {
    struct foo f = {0};
    if (f.a->s) {
        printf("%d\n",f.a->s);
        // printf(f.a->s); //访问的是0x4地址所指向的值，core
    }
    // printf("%d\n", f.a->len);  // core dump
    printf("%d\n", &(f.a->len));
}

// http://coolshell.cn/articles/11377.html
//
int main(int argc, const char *argv[])
{
    test1();
    test2();
    return 0;
}
