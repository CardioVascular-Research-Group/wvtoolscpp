//
// Created by ran on 7/5/16.
//

#ifndef WVTOOLS_TSUIDCACHE_H
#define WVTOOLS_TSUIDCACHE_H

#include <string>
#include <unordered_map>

class TsuidCache {
public:
    TsuidCache();
    bool contains(const std::string& metric, const std::string& subject_id);
    bool contains_subject(const std::string& subject_id);
    std::string get_tsuid(const std::string& metric, const std::string& subject_id);
    void put(const std::string& metric, const std::string& subject_id, const std::string& tsuid);
private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> tsuids;
};


#endif //WVTOOLS_TSUIDCACHE_H
