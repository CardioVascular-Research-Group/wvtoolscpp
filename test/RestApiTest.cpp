//
// Created by rliu14 on 6/28/16.
//

#include <gtest/gtest.h>

#include "restclient-cpp/restclient.h"
#include "json.hpp"

using nlohmann::json;

using RestClient::Response;

using std::cout;
using std::endl;

TEST(rest_api_tests, test_version) {

    Response response = RestClient::get("http://localhost:3001/api/version");

    EXPECT_EQ(200, response.code);
    EXPECT_EQ('{', response.body[0]);

    auto parsed_response = json::parse(response.body);

    EXPECT_STRNE(parsed_response["host"], "null");
    EXPECT_STRNE(parsed_response["short_revision"], "null");

}