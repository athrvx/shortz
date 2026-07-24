#include "UrlService.h"

ShortenResponse UrlService::shortenUrl(const ShortenRequest& request){
    ShortenResponse response;

    response.success = false;
    response.error = "Not implemented";

    return response;
}

std::string UrlService::getOriginalUrl(const std::string& shortCode){
    return "";
}