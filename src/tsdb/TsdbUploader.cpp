//
// Created by rliu14 on 6/28/16.
//

#include "TsdbUploader.h"


TsdbUploader::TsdbUploader(const unsigned long &data_points_per_query, const std::string &tsdb_api_root) {
    this->data_points_per_entry = data_points_per_query;
    this->api_root = tsdb_api_root;
}

