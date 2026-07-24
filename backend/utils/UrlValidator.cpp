#include "UrlValidator.h"
#include <regex>

bool UrlValidator::isValid(const std::string& url){
    static const std::regex pattern(
        R"(^(https?:\/\/)([\w\-]+\.)+[\w\-]+(\/.*)?$)",
        std::regex::icase
    );

    return std::regex_match(url, pattern);
}