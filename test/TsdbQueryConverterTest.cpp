//
// Created by rliu14 on 6/30/16.
//

#include <gtest/gtest.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include "../src/tsdb/TsdbQueryConverter.h"

using namespace boost::posix_time;

using std::cout;
using std::endl;

TEST(tsdb_query_converter_test, test_annotation_generation) {

    // Mock info reader object.
    InfoReader info_reader;
    info_reader.sample_rate = 125;
    info_reader.channel_labels = {"a", "b", "c", "d"};


    TimestampCalculator timestamp_calculator("%Y-%m-%d %H:%M:%s", second_clock::universal_time(), info_reader.sample_rate);
    TsdbQueryConverter converter("awooga", info_reader, timestamp_calculator);

    std::vector<bool> qualities = {true, true, false, true, false, true};
    auto annotations = converter.convert_quality_annotations(qualities);

    for (auto &a : annotations) {

        nlohmann::json j;
        j["description"] = a.description;
        j["start_time"] = a.start_time;
        j["end_time"] = a.end_time;
        cout << j.dump(4) << endl;
    }

}

TEST(tsdb_query_converter_test, test_metric_nomenclature) {

    InfoReader info_reader;
    info_reader.sample_rate = 125;
    info_reader.channel_labels = {"ECG", "ECG", "asdf", "asdf", "ecg"};

    TimestampCalculator timestamp_calculator("%Y-%m-%d %H:%M:%s", second_clock::universal_time(), info_reader.sample_rate);
    TsdbQueryConverter converter("awooga", info_reader, timestamp_calculator);


    for (auto &s : converter.metrics) {
        cout << s << endl;
    }
}