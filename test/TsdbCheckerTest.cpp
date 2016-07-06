//
// Created by ran on 7/6/16.
//

#include <gtest/gtest.h>
#include "../src/tsdb/TsdbChecker.h"

TEST(tsdb_checker_test, test_presence) {

    TsdbChecker checker("http://localhost:3001");
    checker.check_presence("asdf", "asdf", 123);

}