//
// Created by rliu14 on 6/16/16.
//

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <WvToolsFacade.h>

using std::ostream;
using std::cout;
using std::endl;
using std::exception;
using std::cerr;
using std::string;

void print_help(const po::options_description& description, ostream& os) {
    os << description << endl;
}

int main(int argc, const char** argv) {

    double version_number = 1.1;

    po::options_description required("Required options");
    // At first, I thought this was a clever case of using function pointers to return a function from another function.
    // Then I realized it's an abomination of operator overloading.
    required.add_options()
            ("record,r", po::value<string>(), "Record prefix of waveform data to read");

    po::options_description allowed("Allowed options");
    allowed.add_options()
            ("help,h", "Prints program usage help")
            ("unscaled,u", "If this option is passed, the program prints unscaled data. Scaled is the default.")
            ("physionet,p", "If this option is passed, the program writes a physionet header instead of amplitudes")
            ("checksums,c", "If this option is passed, the program prints the checksums for each channel")
            ("timestamps,t", "If this option is passed, the timestamps column is included")
            ("no-headers,h", "If this option is passed, the headers row is omitted")
            ("quality,q", po::value<int>(), "If this option is passed, the program outputs quality annotations with the specified threshold.")
            ("channel,x", po::value<int>(), "Quality values are emitted for the specified channel (0-indexed).")
            ("num-channels,n", "Program writes the number of channels contained in a record.")
            ("version,v", "Prints version information for program.");

    try {
        // Parse command line, store in argument map.
        po::options_description all("All options");
        all.add(required).add(allowed);

        po::variables_map argument_map;
        po::store(po::parse_command_line(argc, argv, all), argument_map);
        po::notify(argument_map);

        if (argument_map.count("help")) {
            print_help(required, cout);
            print_help(allowed, cout);
        } else {

            string prefix = argument_map["record"].as<string>();

            bool timestamps = argument_map.count("timestamps") > 0;
            bool headers = argument_map.count("no-headers") == 0;
            bool physionet = argument_map.count("physionet") > 0;
            bool checksums = argument_map.count("checksums") > 0;
            bool scaled = argument_map.count("unscaled") == 0;
            bool quality = argument_map.count("quality") > 0;
            bool num_channels = argument_map.count("num-channels") > 0;
            bool version = argument_map.count("version") > 0;

            // Could do some more input validation, but if the user wants to put in contradictory parameters,
            // they can live with unpredictable behavior.

            WvToolsFacade facade;

            if (physionet) {
                facade.write_physionet(cout, prefix);
            } else if (checksums) {
                facade.write_checksums(cout, prefix);
            } else if (quality) {
                unsigned int threshold = (unsigned)argument_map["quality"].as<int>();
                unsigned int channel = (unsigned)argument_map["channel"].as<int>();

                facade.write_quality(cout, prefix, channel, threshold);
            } else if (num_channels) {
                facade.write_num_channels(cout, prefix);
            } else if (version) {
                cout << version_number << endl;
            } else {
                facade.write_data(cout, prefix, scaled, headers, timestamps);
            }
        }

    } catch (exception& e) {
        cerr << e.what() << endl;
        print_help(required, cerr);
        print_help(allowed, cerr);
    }
}