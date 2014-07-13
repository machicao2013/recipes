// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/program_options.hpp>

#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;


// A helper function to simplify the main part.
template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    copy(v.begin(), v.end(), ostream_iterator<T>(cout, " "));
    return os;
}

int main(int ac, char* av[])
{
    try {
        int opt;
        int portnum;
        boost::program_options::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("optimization", boost::program_options::value<int>(&opt)->default_value(10),
             "optimization level")
            ("verbose,v", boost::program_options::value<int>()->implicit_value(1),
             "enable verbosity (optionally specify level)")
            ("listen,l", boost::program_options::value<int>(&portnum)->implicit_value(1001)->default_value(0,"no"),
             "listen on a port.")
            ("include-path,I", boost::program_options::value< vector<string> >(),
             "include path")
            ("input-file", boost::program_options::value< vector<string> >(), "input file")
            ;

        boost::program_options::positional_options_description p;
        p.add("input-file", -1);

        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::command_line_parser(ac, av).options(desc).positional(p).run(), vm);
        boost::program_options::notify(vm);

        if (vm.count("help")) {
            cout << "Usage: options_description [options]\n";
            cout << desc;
            return 0;
        }

        if (vm.count("include-path"))
        {
            cout << "Include paths are: " << vm["include-path"].as< vector<string> >() << "\n";
        }

        if (vm.count("input-file"))
        {
            cout << "Input files are: "
                << vm["input-file"].as< vector<string> >() << "\n";
        }

        if (vm.count("verbose")) {
            cout << "Verbosity enabled.  Level is " << vm["verbose"].as<int>()
                << "\n";
        }

        cout << "Optimization level is " << opt << "\n";

        cout << "Listen port is " << portnum << "\n";
    }
    catch(std::exception& e)
    {
        cout << e.what() << "\n";
        return 1;
    }
    return 0;
}
