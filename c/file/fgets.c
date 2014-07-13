#include <stdio.h>

/*
 *  fgets会读取回车和换行符，并且在最后会添加一个\0结束
 */
int main()
{
    FILE *pfile = fopen("argc.c", "r");
    if (pfile == NULL)
    {
        printf("%s\n", "open file error");
        return -1;
    }
    char buf[2048 + 1];
    while((fgets(buf, 2049, pfile)) != NULL) {
        printf("%s", buf);
    }
    fclose(pfile);
    return 0;
}

