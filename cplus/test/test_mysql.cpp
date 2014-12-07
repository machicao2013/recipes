#include<mysql.h>
#include<stdio.h>

int main()
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","root", "945497622", NULL, 0, NULL, 0))
    {
        printf("Error connecting to database:%s\n",mysql_error(&mysql));
    }
    else
    {
        printf("Connect mysql server success........\n");
    }
    mysql_close(&mysql);

    return 0;
}
