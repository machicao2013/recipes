#include <iostream>
#include <boost/regex.hpp>

using namespace std;
int main()
{
    //( 1 )   ((  3  )  2 )((  5 )4)(    6    )
    //(\w+)://((\w+\.)*\w+)((/\w*)*)(/\w+\.\w+)?
    //    //^协议://网址(x.x...x)/路径(n个\字串)/网页文件(xxx.xxx)
    const char *szReg = "(\\w+)://((\\w+\\.)*\\w+)((/\\w*)*)(/\\w+\\.\\w+)?";
    const char *szStr = "http://www.cppprog.com/2009/0112/48.html";

    cout << "test1: common case " << endl;
    {
        boost::regex reg(szReg);
        bool r = boost::regex_match(szStr, reg);
        assert(r);
    }
    cout << "test2: " << endl;
    {
        boost::regex reg1(szReg, boost::regex::perl | boost::regex::icase);
        boost::regex reg2(szReg, boost::regex::extended);
    }
    cout << "test3: get substr" << endl;
    {
        boost::cmatch mat;
        boost::regex reg(szReg);
        bool r = boost::regex_match(szStr, mat, reg);
        if (r) {
            for(boost::cmatch::iterator itr = mat.begin(); itr != mat.end(); ++itr) {
                cout << itr->first - szStr << " : " << itr->second - szStr << " : " << *itr << endl;
            }
            if (mat[4].matched) {
                cout << "Path is " << mat[4] << endl;
            }
        }
    }
    cout << "test4: search test" << endl;
    {
        boost::cmatch mat;
        boost::regex reg("\\d+");
        if (boost::regex_search(szStr, mat, reg)) {
            cout << "searched: " << mat[0] << endl;
        }
    }
    cout << "test5: replace test" << endl;
    {
        boost::regex reg(szReg);
        string s = boost::regex_replace(string(szStr), reg, "ftp://$2$5");
        cout << "ftp site: " << s << endl;
    }
    return 0;
}
