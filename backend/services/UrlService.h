#pragma once

#include <optional>
#include <string>

#include "Database.h"
#include "../utils/Base62.h"
#include "../utils/UrlValidator.h"
#include <sqlite3.h>

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
        explicit UrlService(Database& database);

        ShortenResponse shortenUrl(const ShortenRequest& request);

        std::optional<std::string> getOriginalUrl(const std::string& shortCode);

    private:
        Database& database_;

        std::optional<std::string> findExistingShortCode(const std::string& url);

        bool aliasExists(const std::string& alias);

        int insertUrl(const std::string& url);

        bool updateShortCode(int id, const std::string& code);
};