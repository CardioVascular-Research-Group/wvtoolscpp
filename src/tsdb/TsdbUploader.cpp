//
// Created by rliu14 on 6/28/16.
//

#include <restclient-cpp/restclient.h>
#include "TsdbUploader.h"

using nlohmann::json;

using std::string;
using std::vector;

using std::cout;
using std::endl;

TsdbUploader::TsdbUploader(const unsigned long &data_points_per_query, const std::string &tsdb_api_root) {
    this->max_queue_length = data_points_per_query;
    this->api_root = tsdb_api_root;
}


void TsdbUploader::add_data_point(const TsdbUploader::data_entry entry) {
    entry_queue.push_back(entry);
    if (entry_queue.size() >= max_queue_length) {
        flush();
    }
}

void TsdbUploader::add_data_point(const std::string &metric, const unsigned long &timestamp, const double &value,
                                  const std::unordered_map<std::string, std::string> &tags) {
    data_entry data;
    data.metric = metric;
    data.timestamp = timestamp;
    data.value = value;
    data.tags = tags;
    add_data_point(data);
}

void TsdbUploader::add_annotation(const std::string &metric, const unsigned long &start_time,
                                  const unsigned long &end_time, const std::string &description,
                                  const std::unordered_map<std::string, std::string> &tags) throw (IOException) {
    // First, we need to query and find the TSUID of the series.
    string tsuid = query_tsuid(metric, start_time, tags);

    json query = {
            {"startTime", start_time},
            {"endTime", end_time},
            {"tsuid", tsuid},
            {"description", description}
    };

    RestClient::Response response = RestClient::post(api_root + "/api/annotation", "application/json", query.dump());
    if (response.code != 204) {
        throw IOException(response.body);
    }
}


std::string TsdbUploader::query_tsuid(const std::string &metric, const unsigned long &start_time, const std::unordered_map<std::string, std::string> &tags) {

    vector<json> queries;
    queries.push_back({{"aggregator", "avg"}, {"metric", metric}, {"tags", tags}});

    json query = {
            {"metric", metric},
            {"start", start_time},
            {"end", start_time + 8},
            {"queries", queries},
            {"msResolution", true},
            {"showTSUIDs", true}
    };

    RestClient::Response response = RestClient::post(api_root + "/api/query", "application/json", query.dump());
    auto parsed_response = json::parse(response.body);
    json query_response = parsed_response[0];

    return query_response["tsuids"][0];
}


void TsdbUploader::flush() throw (IOException) {
    if (entry_queue.size() > 0) {
        vector<json> json_entries;
        for (auto &e : entry_queue) {
            json_entries.push_back(create_json_entry(e));
        }

        json query(json_entries);

        RestClient::Response response = RestClient::post(api_root + "/api/put", "application/json", query.dump());
        if (response.code != 204) {
            throw IOException(response.body);
        }

        entry_queue.clear();
    }
}


nlohmann::json TsdbUploader::create_json_entry(const TsdbUploader::data_entry &entry) {
    json result;

    result["metric"] = entry.metric;
    result["timestamp"] = entry.timestamp;
    result["value"] = entry.value;
    result["tags"] = json(entry.tags);

    return result;
}


