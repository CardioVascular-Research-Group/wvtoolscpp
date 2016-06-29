//
// Created by rliu14 on 6/29/16.
//

#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time.hpp>

class TimestampCalculator {
public:
    TimestampCalculator(const std::string& format, const boost::posix_time::ptime& base_time, const double& sample_rate);
    std::string format_time(const boost::posix_time::ptime& time);
    std::string format_time(const unsigned long& index);
    boost::posix_time::ptime calculate_offset(const unsigned long& index);
private:
    long increment;
    std::locale current_locale;
    boost::posix_time::ptime base_time;
};


