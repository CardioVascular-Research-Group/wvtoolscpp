//
// Created by ran on 7/5/16.
//

#include <restclient-cpp/restclient.h>
#include <json.hpp>

#include "TsdbChecker.h"
#include "TsdbQueryConverter.h"

#include <cmath>

using nlohmann::json;

using std::vector;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::to_string;

using std::abs;

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
    vector<vector<json>> queries;

    TsdbQueryConverter converter(prefix, info_reader, timestamp_calculator);

    for (unsigned long c = 0; c < info_reader.num_channels(); c++) {
        result.push_back(true);
        queries.push_back(vector<json>());

        queries[c].push_back(
                {
                        {"aggregator", "avg"},
                        {"metric", converter.metrics[c]},
                        {"tags", {{"subject_id", prefix}}}
                }
        );
    }

    unsigned long current_index = 0;

    while (current_index < wv_reader.num_entries() / info_reader.num_channels()) {
        cerr << " " << (double)current_index / wv_reader.num_entries() * info_reader.num_channels() * 100 << "%" << "\r";

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
        auto start_time = timestamp_calculator.calculate_timestamp(timestamp_calculator.calculate_offset(current_index));
        auto end_time = timestamp_calculator.calculate_timestamp(timestamp_calculator.calculate_offset(current_index + query_size - 1));

        for (unsigned long c = 0; c < info_reader.num_channels(); c++) {
            json query = {
                    {"start", start_time},
                    {"end", end_time},
                    {"msResolution", true},
                    {"noAnnotations", true},
                    {"queries", queries[c]}
            };

            RestClient::Response response = RestClient::post(tsdb_root + "/api/query", "application/json", query.dump());
            if (response.code != 200 || response.body == "[]") {
                result[c] = false;
                continue;
            }

            auto parsed_response = json::parse(response.body);
            json query_response = parsed_response[0];
            json data_points = query_response["dps"];

            for (unsigned long i = 0; i < actual_values[0].size(); i++) {

                auto timestamp = to_string(timestamp_calculator.calculate_timestamp(timestamp_calculator.calculate_offset(current_index + i)));
                double value = data_points[timestamp];

                double difference = abs(value - actual_values[c][i]);
                // Tolerance of 10% of the least significant bit.
                if (difference > info_reader.gains[c] / 10) {
                    result[c] = false;
                    cout << "Mismatch for channel " + converter.metrics[c] << endl;
                    cout << "queried: " << value << ", actual: " << actual_values[c][i] << endl;
                }

            }
        }

        current_index += query_size;
    }
    cerr << " 100%    " << endl;

    return result;
}


std::vector<double> TsdbChecker::read(const std::string &prefix, const std::string &metric, const unsigned long &start_time) {
    return std::vector<double>();
}

