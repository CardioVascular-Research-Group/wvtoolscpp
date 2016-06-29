//
// Created by rliu14 on 6/28/16.
//

#include "TsdbUploader.h"

using nlohmann::json;

TsdbUploader::TsdbUploader(const unsigned long &data_points_per_query, const std::string &tsdb_api_root) {
    this->max_queue_length = data_points_per_query;
    this->api_root = tsdb_api_root;
}


void TsdbUploader::add_data_point(const std::string &metric, const unsigned long &timestamp, const double &value,
                                  const std::unordered_map<std::string, std::string> &tags) {
    data_entry data;
    data.metric = metric;
    data.timestamp = timestamp;
    data.value = value;
    data.tags = tags;
    entry_queue.push_back(data);

    if (entry_queue.size() == max_queue_length) flush();
}

void TsdbUploader::add_annotation(const std::string &metric, const unsigned long &start_time,
                                  const unsigned long &end_time, const std::string &description,
                                  const std::unordered_map<std::string, std::string> &tags) {

}

void TsdbUploader::flush() {
    json entry;

    entry_queue.clear();
}


nlohmann::json TsdbUploader::create_json_entry(const TsdbUploader::data_entry &entry) {
    json result;

    result["metric"] = entry.metric;
    result["timestamp"] = entry.timestamp;
    result["value"] = entry.value;
    result["tags"] = json(entry.tags);

    return result;
}


