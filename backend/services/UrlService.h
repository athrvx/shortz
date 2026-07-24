#pragma once

#include <string>

struct ShortenRequest{
    std::string url;
    std::string customAlias;
};

struct ShortenResponse{
    bool success = false;
    std::string shortCode;
    std::string shortUrl;
    std::string error;
};

class UrlService{
    public:
        ShortenResponse shortenUrl(const ShortenRequest& request);

        std::string getOriginalUrl(const std::string& shortCode);
};