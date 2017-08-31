//
// Created by FyS on 28/08/17.
//

#include <vector>
#include <iostream>
#include "HttpAuthClient.hh"

fys::network::HttpAuthClient::~HttpAuthClient() {
    curl_easy_cleanup(_curl);
}

fys::network::HttpAuthClient::HttpAuthClient() : _curl(curl_easy_init()) {
    if (_curl)
        curl_easy_setopt(_curl, CURLOPT_URL, URL_SERVICE);
}

bool fys::network::HttpAuthClient::authenticate(const std::string& user, const std::string& password) {
    CURLcode res;

    if (_curl)
        curl_easy_setopt(_curl, CURLOPT_USERPWD, user + ":" + password);
    res = curl_easy_perform(_curl);
    std::cout << res << std::endl;
    return res == CURLE_OK;
}


