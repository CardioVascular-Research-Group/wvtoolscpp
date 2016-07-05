//
// Created by ran on 7/5/16.
//

#include "TsuidCache.h"

using std::unordered_map;

TsuidCache::TsuidCache() {

}

bool TsuidCache::contains(const std::string &metric, const std::string &subject_id) {
    if (contains_subject(subject_id)) return tsuids[subject_id].find(metric) != tsuids[subject_id].end();
    return false;
}


bool TsuidCache::contains_subject(const std::string &subject_id) {
    return tsuids.find(subject_id) != tsuids.end();
}


std::string TsuidCache::get_tsuid(const std::string &metric, const std::string &subject_id) {
    return tsuids[subject_id][metric];
}


void TsuidCache::put(const std::string &metric, const std::string &subject_id, const std::string &tsuid) {
    tsuids[subject_id][metric] = tsuid;
}
