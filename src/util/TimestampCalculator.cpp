//
// Created by rliu14 on 6/29/16.
//

#include "TimestampCalculator.h"

using namespace boost::gregorian;
using namespace boost::posix_time;

using std::locale;
using std::stringstream;

TimestampCalculator::TimestampCalculator(const std::string &format, const boost::posix_time::ptime &base_time, const double& sample_rate)
        : base_time(base_time), current_locale(locale("en_US.utf8"), new time_facet(format.c_str())) { // Not a memory leak, the locale takes ownership and is implicitly destructed.
    this->increment = (long)(1000 / sample_rate);
}

boost::posix_time::ptime TimestampCalculator::calculate_offset(const unsigned long &index) {
    return base_time + milliseconds(index * increment);
}

std::string TimestampCalculator::format_time(const unsigned long &index) {
    return format_time(calculate_offset(index));
}

std::string TimestampCalculator::format_time(const boost::posix_time::ptime &time) {
    stringstream stream;
    stream.imbue(current_locale);

    stream << time;

    return stream.str();
}


long TimestampCalculator::calculate_timestamp(const boost::posix_time::ptime &time) {
    static ptime epoch(date(1970, 1, 1));
    auto difference = time - epoch;
    return difference.total_milliseconds();
}

