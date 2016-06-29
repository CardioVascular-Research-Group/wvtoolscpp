//
// Created by rliu14 on 6/29/16.
//

#include "TimestampCalculator.h"

using namespace boost::gregorian;
using namespace boost::date_time;

using std::locale;

TimestampCalculator::TimestampCalculator(const std::string &format, const boost::posix_time::ptime &base_time)
        : base_time(base_time), current_locale(locale("en_US.utf8"), new time_facet("")) { // Not a memory leak, the locale takes ownership and is implicitly destructed.

}

