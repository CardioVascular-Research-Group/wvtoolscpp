//
// Created by rliu14 on 6/28/16.
//

#pragma once

#include <string>

/**
 * Handles upload to TSDB via REST query.
 */
class TsdbUploader {
public:
    TsdbUploader(const unsigned long& data_points_per_query, const std::string& tsdb_api_root);
private:
    unsigned long data_points_per_entry;
    std::string api_root;
};


