//
// Created by ran on 7/5/16.
//

#include <restclient-cpp/restclient.h>
#include <json.hpp>

#include "TsdbChecker.h"
#include "TsdbQueryConverter.h"

using nlohmann::json;

using std::vector;
using std::string;
using std::cout;
using std::endl;

TsdbChecker::TsdbChecker(const string& tsdb_root) : tsdb_root(tsdb_root) {

}

bool TsdbChecker::check_presence(const std::string &metric, const std::string &subject_id, const unsigned long& start_time) {

    vector<json> queries;
    queries.push_back(
            {
                    {"aggregator", "avg"},
                    {"metric", metric},
                    {"tags", {{"subject_id", subject_id}}}
            }
    );

    json query = {
            {"start", start_time},
            {"end", start_time + 8},
            {"msResolution", true},
            {"queries", queries}
    };

    RestClient::Response response = RestClient::post(tsdb_root + "/api/query", "application/json", query.dump());
    return (response.code == 200) && (response.body != "[]");
}


std::vector<bool> TsdbChecker::validate(const string& prefix, InfoReader &info_reader, WvReader &wv_reader, TimestampReader &timestamp_reader, TimestampCalculator &timestamp_calculator, const int &query_size) {
    vector<bool> result;

    unsigned long current_index = 0;

    TsdbQueryConverter converter(prefix, info_reader, timestamp_calculator);

    while (current_index < wv_reader.num_entries() / info_reader.num_channels()) {

        // Read actual values from file.
        vector<vector<double>> actual_values;
        // Initialize
        for (unsigned long c = 0; c < info_reader.num_channels(); c++) {
            actual_values.push_back(vector<double>());
        }
        for (unsigned long c = 0; c < info_reader.num_channels() * query_size && wv_reader.has_next(); c++) {
            auto channel_index = c % info_reader.num_channels();
            actual_values[channel_index].push_back(info_reader.gains[channel_index] * wv_reader.next());
        }

        // Query the channels.


        current_index += query_size;
    }


    return result;
}

