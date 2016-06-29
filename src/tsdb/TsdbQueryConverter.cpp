//
// Created by rliu14 on 6/29/16.
//

#include "TsdbQueryConverter.h"

using nlohmann::json;

TsdbQueryConverter::TsdbQueryConverter(const std::string& prefix, InfoReader &info_reader, TimestampCalculator& timestamp_calculator) : info_reader(info_reader), timestamp_calculator(timestamp_calculator) {
    this->prefix = prefix;
    current_index = 0;
}


TsdbUploader::data_entry TsdbQueryConverter::convert_scaled_data(const double &scaled_data_point) {
    auto current_channel = current_index % info_reader.num_channels();
    auto current_offset = current_index++ / info_reader.num_channels();

    TsdbUploader::data_entry entry;
    entry.metric = metrics[current_channel];
    entry.timestamp = (unsigned long)timestamp_calculator.calculate_timestamp(timestamp_calculator.calculate_offset(current_offset));
    entry.tags = {{"subject_id", prefix}};
    entry.value = scaled_data_point;

    return entry;
}

