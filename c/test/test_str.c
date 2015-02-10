#include <iostream>

int main()
{
    char str1[] = "abc";
    char str2[] = "abc";
    const char str3[] = "abc";
    const char str4[] = "abc";

    const char *str5 = "abc";
    const char *str6 = "abc";
    char *str7 = "abc";
    char *str8 = "abc";

    std::cout << (str1 == str2) << std::endl;
    std::cout << (str3 == str4) << std::endl;
    std::cout << (str5 == str6) << std::endl;
    std::cout << (str7 == str8) << std::endl;

    str1[1] = 'd';
    // str3[1] = 'd';
    return 0;
}

