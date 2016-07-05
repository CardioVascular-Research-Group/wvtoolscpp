//
// Created by rliu14 on 7/5/16.
//

#include <gtest/gtest.h>

#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
using namespace boost::program_options;
using boost::algorithm::split;
using boost::algorithm::is_any_of;
using std::cout;
using std::endl;
using std::string;
using std::vector;

TEST(config_file_read_test, read_test) {
    options_description desc;
    desc.add_options()
            ("message", value<string>(), "A message to print")
            ("vector", value<string>(), "A list of messages to print");

    variables_map vm;
    store(parse_config_file<char>("data/test.cfg", desc), vm);
    notify(vm);


    cout << vm["message"].as<string>() << endl;

    vector<string> messages;
    split(messages, vm["vector"].as<string>(), is_any_of(","));

    for (auto &s : messages) {
        cout << s << endl;
    }
}

TEST(config_file_read_test, override_test) {

    const char* argv[] = {"wvtools", "--vector", "awooga,awwoga"};
    int argc = 3;

    options_description desc;
    desc.add_options()
            ("message", value<string>(), "A message to print")
            ("vector", value<string>(), "A list of messages to print");

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    store(parse_config_file<char>("data/test.cfg", desc), vm);
    notify(vm);

    cout << vm["message"].as<string>() << endl;

    vector<string> messages;
    split(messages, vm["vector"].as<string>(), is_any_of(","));

    for (auto &s : messages) {
        cout << s << endl;
    }

}