//
// Created by ran on 7/5/16.
//

#ifndef WVTOOLS_TSDBCHECKER_H
#define WVTOOLS_TSDBCHECKER_H

#include <string>
using std::string;

class TsdbChecker {
public:
    TsdbChecker();
    bool check_presence(const std::string& metric, const std::string& subject_id);

private:

};


#endif //WVTOOLS_TSDBCHECKER_H
