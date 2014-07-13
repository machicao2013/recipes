#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
int main()
{
    MYSQL mysql;//连接数据库的变量
    MYSQL_RES *res;//存放查询结果的变量
    MYSQL_ROW row;
    char *query;
    int t,r;
    char *server= "10.10.13.34";
    char *user = "root";
    char *password="snakeman";
    char *database = "sandai_hub";
    mysql_init(&mysql); //连接数据库前，必须调用此函数初始化变量
    if(!mysql_real_connect(&mysql,server,user,password,database,0/*TCP IP端口*/,NULL/*Unix socket连接类型*/,0/*运行成ODBC数据库的标记*/)) {
        printf("Error connection to database:%s/n",mysql_error(&mysql));
    } else {
        printf("Connected.../n");
    }
    query = "select tableName, mysqlPort  from sd_hash_table_db_map";
    printf("query execute:%s/n",query);
    t = mysql_real_query(&mysql,query,(unsigned int) strlen(query));
    if(t) {
        printf("Error making query:%s/n",mysql_error(&mysql));
    } else {
        printf("[%s] made.../n",query);
    }
    res = mysql_store_result(&mysql);
    while(row = mysql_fetch_row(res)) {
        for(t=0;t<=mysql_num_fields(res);t++) {
            printf("%s",row[t]);
        }
        printf("/n");
    }
    printf("mysql_free_result.../n");
    mysql_free_result(res);
    mysql_close(&mysql);
    return 1;
}
//编译：gcc testsql.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient -o testsql

