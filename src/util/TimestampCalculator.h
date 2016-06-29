//
// Created by rliu14 on 6/29/16.
//

#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time.hpp>

class TimestampCalculator {
public:
    TimestampCalculator(const std::string& format, const boost::posix_time::ptime& base_time);
private:
    std::locale current_locale;
    boost::posix_time::ptime base_time;
};


