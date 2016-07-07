//
// Created by ran on 7/5/16.
//

#include <restclient-cpp/restclient.h>
#include <json.hpp>

#include "TsdbChecker.h"

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
    query["start"] = start_time;
    query["end"] = start_time + 8;
    query["msResolution"] = true;

    RestClient::Response response = RestClient::post(tsdb_root + "/api/query", "application/json", query.dump());
    return (response.code == 200) && (response.body != "[]");
}

bool TsdbChecker::validate(const std::string &metric, const std::string &subject_id, WvReader &wv_reader, InfoReader &info_reader, TimestampReader& timestamp_reader) {

    return false;
}

