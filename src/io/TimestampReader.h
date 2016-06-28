//
// Created by rliu14 on 6/28/16.
//

#pragma once

#include <gtest/gtest.h>

#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>
#include "IOException.h"

/**
 * Reads timestamps.
 */
class TimestampReader {
public:
    TimestampReader(const std::string& prefix) throw (IOException);
private:
    boost::posix_time::ptime start_time;

    FRIEND_TEST(timestamp_test, timestamp_reader_test);
};


