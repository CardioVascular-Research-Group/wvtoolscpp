//
// Created by rliu14 on 6/28/16.
//

#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "json.hpp"

#include <gtest/gtest.h>

/**
 * Handles upload to TSDB via REST query.
 */
class TsdbUploader {
public:
    struct data_entry {
        std::string metric;
        unsigned long timestamp;
        double value;
        std::unordered_map<std::string, std::string> tags;
    };

    TsdbUploader(const unsigned long& data_points_per_query, const std::string& tsdb_api_root);

    void add_data_point(const std::string& metric, const unsigned long& timestamp, const double& value, const std::unordered_map<std::string, std::string>& tags);
    void add_annotation(const std::string& metric, const unsigned long& start_time, const unsigned long& end_time, const std::string& description, const std::unordered_map<std::string, std::string>& tags);
    void flush();

private:
    unsigned long max_queue_length;
    std::vector<data_entry> entry_queue;

    std::string api_root;

    static nlohmann::json create_json_entry(const data_entry& entry);

    FRIEND_TEST(tsdb_uploader_test, create_json_entry_test);
};


