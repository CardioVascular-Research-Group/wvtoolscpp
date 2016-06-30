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

void print_version_information(ostream& os) {
    double version_number = 1.2;
    os << "WvTools, version " << version_number << ", updated June 27th, 2016" << endl;
    os << "Author: Ran Liu, rliu14@jhu.edu" << endl;
}

void print_help(const po::options_description& description, ostream& os) {
    os << description << endl;
}

int main(int argc, const char** argv) {

    po::options_description required("Required options");
    // At first, I thought this was a clever case of using function pointers to return a function from another function.
    // Then I realized it's an abomination of operator overloading.
    required.add_options()
            ("record,r", po::value<string>(), "Record prefix of waveform data to read");

    po::options_description modes("Operating modes");
    modes.add_options()
            ("version,v", "Prints version information for program.")
            ("help,h", "Prints program usage help")
            ("unscaled,u", "If this option is passed, the program prints unscaled data. Scaled is the default.")
            ("physionet,p", "If this option is passed, the program writes a physionet header instead of amplitudes")
            ("checksums,c", "If this option is passed, the program prints the checksums for each channel")
            ("features,f", "If this option is passed, the program emits the feature vectors for the specified channel")
            ("quality,q", "If this option is passed, the program outputs quality annotations.")
            ("num-channels,n", "Program writes the number of channels contained in a record.")
            ("tsdb,t", po::value<string>(), "Uploads data and quality annotations to TSDB.")
            ("tsdb-annotations", po::value<string>(), "Uploads only quality annotations to TSDB.");


    po::options_description allowed("Allowed options");
    allowed.add_options()
            ("no-headers", "If this option is passed, the headers row is omitted")
            ("svm,s", po::value<string>(), "Passes a file containing SVM parameters for quality checking.")
            ("channel,x", po::value<int>(), "Quality values are emitted for the specified channel (0-indexed).")
            ("annotations,a", po::value<string>(), "Filename containing QRS onset annotations.");

    try {
        // Parse command line, store in argument map.
        po::options_description all("All options");
        all.add(required).add(modes).add(allowed);

        po::variables_map argument_map;
        po::store(po::parse_command_line(argc, argv, all), argument_map);
        po::notify(argument_map);

        if (argument_map.count("help")) {
            print_help(required, cout);
            print_help(modes, cout);
            print_help(allowed, cout);
        } else if (argument_map.count("version")) {
            print_version_information(cout);
        } else {

            string prefix = argument_map["record"].as<string>();

            bool headers = argument_map.count("no-headers") == 0;
            bool physionet = argument_map.count("physionet") > 0;
            bool checksums = argument_map.count("checksums") > 0;
            bool scaled = argument_map.count("unscaled") == 0;
            bool quality = argument_map.count("quality") > 0;
            bool num_channels = argument_map.count("num-channels") > 0;
            bool features = argument_map.count("features") > 0;
            bool tsdb = argument_map.count("tsdb") > 0;
            bool tsdb_annotations = argument_map.count("tsdb-annotations") > 0;

            // Could do some more input validation, but if the user wants to put in contradictory parameters,
            // they can live with unpredictable behavior.

            WvToolsFacade facade;

            if (physionet) {
                facade.write_physionet(cout, prefix);
            } else if (checksums) {
                facade.write_checksums(cout, prefix);
            } else if (quality) {
                unsigned int channel = (unsigned) argument_map["channel"].as<int>();
                string svm = argument_map["svm"].as<string>();
                string annotations = argument_map["annotations"].as<string>();
                facade.write_quality(cout, prefix, channel, svm, headers, annotations);
            } else if (features) {
                unsigned int channel = (unsigned) argument_map["channel"].as<int>();
                string annotations = argument_map["annotations"].as<string>();
                facade.write_features(cout, prefix, channel, headers, annotations);
            } else if (num_channels) {
                facade.write_num_channels(cout, prefix);
            } else if (tsdb) {
                unsigned int channel = (unsigned)argument_map["channel"].as<int>();
                string tsdb_root = argument_map["tsdb"].as<string>();
                string svm = argument_map["svm"].as<string>();
                string annotations = argument_map["annotations"].as<string>();
                facade.tsdb_upload(prefix, channel, svm, annotations, tsdb_root);
            } else if (tsdb_annotations) {
                unsigned int channel = (unsigned)argument_map["channel"].as<int>();
                string tsdb_root = argument_map["tsdb-annotations"].as<string>();
                string svm = argument_map["svm"].as<string>();
                string annotations = argument_map["annotations"].as<string>();
                facade.tsdb_annotations_upload(prefix, channel, svm, annotations, tsdb_root);
            } else {
                facade.write_data(cout, prefix, scaled, headers, false);
            }
        }

    } catch (exception& e) {
        cerr << e.what() << endl;
        print_help(required, cerr);
        print_help(modes, cerr);
        print_help(allowed, cerr);
    }
}