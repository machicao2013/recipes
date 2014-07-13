#include <boost/shared_ptr.hpp>
#include <iostream>
#include <cstdio>

class FileCloser
{
public:
    void operator()(FILE *file)
    {
        std::cout << "The FileCloser has been called with a FILE*, which will now be closed.\n";
        if(file != 0)
            fclose(file);
    }
};

int main()
{
    std::cout << "shared_ptr example with a custom deallocator.\n";

    {
        FILE *f = fopen("shared_ptr_test.cpp", "r");
        if (f == 0)
        {
            std::cout << "Unable to open file\n";
            throw "Unable to open file";
        }

        boost::shared_ptr<FILE> my_shared_file(f, FileCloser());
        //boost::shared_ptr<FILE> my_shared_file(f, &fclose);

        fseek(my_shared_file.get(), 42, SEEK_SET);
    }

    std::cout << "By now, the FILE has been closed!\n";
    return 0;
}

