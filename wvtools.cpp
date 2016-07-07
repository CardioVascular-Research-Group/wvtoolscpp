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
using std::vector;

void print_version_information(ostream& os) {
    double version_number = 1.3;
    os << "WvTools, version " << version_number << ", updated July 5th, 2016" << endl;
    os << "Author: Ran Liu, rliu14@jhu.edu" << endl;
}

void print_help(const po::options_description& description, ostream& os) {
    os << description << endl;
}

int main(int argc, const char** argv) {

    po::options_description required("Required options");
    required.add_options()
            ("record,r", po::value<string>(), "Record prefix of waveform data set");

    po::options_description modes("Operating modes");
    modes.add_options()
            ("version", "Prints version information for the program")
            ("help,h", "Prints program usage help")
            ("unscaled", "Prints unscaled data. Scaled is the default, if no operating mode is specified")
            ("physionet,p", "Prints physionet header")
            ("checksum", "Prints checksums for each channel")
            ("features", "Emits feature vectors for specified channel")
            ("quality", "Prints quality annotations for specified channel")
            ("num-channels,n", "Prints number of channels contained in a record")
            ("tsdb,t", "Uploads data and quality annotations to TSDB")
            ("tsdb-annotations", "Uploads only quality annotations to TSDB")
            ("tsdb-check", "Checks if a record is in TSDB already")
            ("tsdb-validate", "Queries a record in TSDB and checks annotations and data against local record")
            ("tsdb-read", po::value<vector<string>>(), "Reads metrics from TSDB");


    po::options_description configurations("Program configurations");
    configurations.add_options()
            ("no-headers", "Omits header row when outputting data")
            ("svm,s", po::value<string>(), "Specifies the file containing the parameters of the SVM used for quality checking")
            ("channel,x", po::value<int>(), "Specifies the index of a channel for modes that operate on a single channel (0-indexed)")
            ("annotations,a", po::value<string>(), "Filename containing QRS onset annotations")
            ("tsdb-root", po::value<string>(), "Url of OpenTSDB api root")
            ("chunk-size", po::value<int>(), "Size of transmission chunk when uploading waveform data to TSDB.")
            ("query-size", po::value<int>(), "Size of transmission chunk when querying waveform data in TSDB for validation.");

    po::options_description config_file_options;
    config_file_options.add(configurations);

    po::options_description command_line_options;
    command_line_options.add(required).add(modes).add(configurations);


    po::variables_map argument_map;
    po::store(po::parse_command_line(argc, argv, command_line_options), argument_map);
    po::store(po::parse_config_file<char>("/etc/wvtools.conf", config_file_options), argument_map);
    po::notify(argument_map);

    if (argument_map.count("help")) {
        print_help(required, cout);
        print_help(modes, cout);
        print_help(configurations, cout);
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
        bool tsdb_check = argument_map.count("tsdb-check") > 0;
        bool tsdb_validate = argument_map.count("tsdb-validate") > 0;

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
            int chunk_size = argument_map["chunk-size"].as<int>();
            unsigned int channel = (unsigned)argument_map["channel"].as<int>();
            string tsdb_root = argument_map["tsdb-root"].as<string>();
            string svm = argument_map["svm"].as<string>();
            string annotations = argument_map["annotations"].as<string>();
            facade.tsdb_upload(prefix, channel, svm, annotations, tsdb_root, chunk_size);
        } else if (tsdb_annotations) {
            unsigned int channel = (unsigned) argument_map["channel"].as<int>();
            string tsdb_root = argument_map["tsdb-root"].as<string>();
            string svm = argument_map["svm"].as<string>();
            string annotations = argument_map["annotations"].as<string>();
            facade.tsdb_annotations_upload(prefix, channel, svm, annotations, tsdb_root);
        } else if (tsdb_check) {
            string tsdb_root = argument_map["tsdb-root"].as<string>();
            facade.tsdb_check(prefix, tsdb_root);
        } else if (tsdb_validate) {
            string tsdb_root = argument_map["tsdb-root"].as<string>();
            int query_size = argument_map["query-size"].as<int>();
            facade.tsdb_validate(prefix, tsdb_root, query_size);
        } else {
            facade.write_data(cout, prefix, scaled, headers, false);
        }

    }

}