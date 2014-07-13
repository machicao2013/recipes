/**
 * @file GetFileCount.cpp
 * @author maxingsong, maxingsong@xunlei.com
 * @version 01
 * @date 2014-03-20
 * @brief
 */

#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
using namespace std;

int main()
{
    DIR *dir = opendir(".");
    if (dir == NULL)
    {
        cout << "opendir(.) error: " << strerror(errno) << endl;
        return -1;
    }

    int count = 0;
    struct dirent *curDir = NULL;
    while (NULL != (curDir = readdir(dir)))
    {
        switch(curDir->d_type)
        {
            case DT_REG:
                count++;
                cout << curDir->d_name << endl;
                break;
            case DT_DIR:
                if(strcmp(curDir->d_name, ".") != 0 &&
                    strcmp(curDir->d_name, "..") != 0)
                {
                    //cout << curDir->d_name << endl;
                }
                break;
            default:
                break;
        }
    }
    closedir(dir);
    cout << "The number of regular file is : " << count << endl;
    return 0;
}


