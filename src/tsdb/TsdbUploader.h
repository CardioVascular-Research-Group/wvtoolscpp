//
// Created by rliu14 on 6/28/16.
//

#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "json.hpp"
#include "../io/IOException.h"
#include "TsuidCache.h"

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

    struct annotation_entry {
        std::string tsuid;
        long start_time;
        long end_time;
        std::string description;
    };

    TsdbUploader(const unsigned long& data_points_per_query, const std::string& tsdb_api_root);

    void add_data_point(const data_entry entry);
    void add_data_point(const std::string& metric, const unsigned long& timestamp, const double& value, const std::unordered_map<std::string, std::string>& tags);
    void add_annotation(const std::string& metric, const std::unordered_map<std::string, std::string>& tags, const annotation_entry& entry);
    void add_annotation(const std::string& metric, const unsigned long& start_time, const unsigned long& end_time, const std::string& description, const std::unordered_map<std::string, std::string>& tags) throw (IOException);
    std::string query_tsuid(const std::string& metric, const unsigned long& start_time, const std::unordered_map<std::string, std::string>& tags);
    void flush() throw (IOException);

private:
    TsuidCache tsuid_cache;

    unsigned long max_queue_length;
    std::vector<data_entry> entry_queue;

    std::string api_root;

    static nlohmann::json create_json_entry(const data_entry& entry);

    FRIEND_TEST(tsdb_uploader_test, create_json_entry_test);
};


