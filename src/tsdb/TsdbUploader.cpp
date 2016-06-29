//
// Created by rliu14 on 6/28/16.
//

#include "TsdbUploader.h"


TsdbUploader::TsdbUploader(const unsigned long &data_points_per_query, const std::string &tsdb_api_root) {
    this->data_points_per_entry = data_points_per_query;
    this->api_root = tsdb_api_root;
}


void TsdbUploader::add_data_point(const std::string &metric, const unsigned long &timestamp, const double &value,
                                  const std::unordered_map<std::string, std::string> &tags) {

}

void TsdbUploader::add_annotation(const std::string &metric, const unsigned long &start_time,
                                  const unsigned long &end_time, const std::string &description,
                                  const std::unordered_map<std::string, std::string> &tags) {

}

void TsdbUploader::flush() {

}

