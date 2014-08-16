#define BOOST_PROGRAM_OPTIONS_NO_LIB
#include <boost/program_options.hpp>
using namespace boost::program_options;
using namespace std;

int main(int argc, const char *argv[])
{
    options_description opts("demo options");

    opts.add_options()
        ("help,H", "just a help info")
        ("filename", value<string>(), "to find a file");

    variables_map vmap;
    store(parse_command_line(argc, argv, opts), vmap);   // 解析存储

    if (vmap.count("help")) {
        cout << opts << endl;
        return 0;
    }

    if (vmap.count("filename")) {
        cout << "find " << vmap["filename"].as<std::string>() << endl;
    }

    if (vmap.empty()) {
        cout << argv[0] << " -H" << endl;
        return 0;
    }
    return 0;
}
