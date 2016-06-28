//
// Created by rliu14 on 6/28/16.
//

#include "TimestampReader.h"

#include <boost/regex.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::posix_time;
using namespace boost::gregorian;

using boost::regex;
using boost::regex_search;
using boost::cmatch;

#include <fstream>
using std::ifstream;
using std::string;
using std::stoi;

TimestampReader::TimestampReader(const std::string &prefix) throw (IOException) {
    static regex date_format("0 ([0-9]+)\\-([0-9]+)\\-([0-9]+)");
    static regex time_format("0 ([0-9]+):([0-9]+):([0-9]+)");

    ifstream file(prefix + ".time.txt");
    string date_line;
    string time_line;

    cmatch matches;

    if (file.is_open()) {
        getline(file, date_line);
        getline(file, time_line);

        unsigned short year;
        unsigned short month;
        unsigned short day;
        int hour;
        int minute;
        int second;

        if (regex_search(date_line.c_str(), matches, date_format)) {
            year = (unsigned short)stoi(matches[1]);
            month = (unsigned short)stoi(matches[2]);
            day = (unsigned short)stoi(matches[3]);
        } else {
            throw IOException("Time annotation file formatted incorrectly!");
        }

        if (regex_search(time_line.c_str(), matches, time_format)) {
            hour = stoi(matches[1]);
            minute = stoi(matches[2]);
            second = stoi(matches[3]);
        } else {
            throw IOException("Time annotation file formatted incorrectly!");
        }

        start_time = ptime(date(year, month, day), hours(hour) + minutes(minute) + seconds(second));

    } else {
        throw IOException("Couldn't open time annotation file");
    }

    file.close();
}
