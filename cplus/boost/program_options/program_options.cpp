#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    std::string zk_host, group_id, name, info, log_conf;

    boost::program_options::options_description options("command line options");
    options.add_options()
        ("help,H","how to use")
        ("zk_host,h",   boost::program_options::value<std::string>(&zk_host)->default_value(""), "zk_host format:ip:port")
        ("group_id,g",   boost::program_options::value<std::string>(&group_id)->default_value(""), "group_id: which group to join")
        ("name,n",   boost::program_options::value<std::string>(&name)->default_value(""), "name: member name")
        ("lofo,i",   boost::program_options::value<std::string>(&info)->default_value(""), "info: member info")
        ("log_conf,l",   boost::program_options::value<std::string>(&log_conf)->default_value(""), "log_conf");
    boost::program_options::variables_map vmap;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, options), vmap);
    boost::program_options::notify(vmap);

    if(vmap.count("help")) {
        std::cout << options << std::endl;
        return 1;
    }

    return 0;
}


