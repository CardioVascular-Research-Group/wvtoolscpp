//
// Created by rliu14 on 6/28/16.
//

#include <gtest/gtest.h>

#include "restclient-cpp/restclient.h"

using RestClient::Response;

using std::cout;
using std::endl;

TEST(rest_api_tests, test_version) {

    Response response = RestClient::get("http://localhost:3001/api/version");

    EXPECT_EQ(200, response.code);
    cout << response.body << endl;
    cout << response.code << endl;


}