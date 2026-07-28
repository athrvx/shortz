#include "UrlController.h"
#include "../services/UrlService.h"

#include <json/json.h>

extern UrlService urlService;

using namespace drogon;

void UrlController::shorten(
    const HttpRequestPtr& request,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto json = request->getJsonObject();

    Json::Value response;

    if(!json){
        response["success"] = false;
        response["error"] = "Invalid JSON";

        callback(HttpResponse::newHttpJsonResponse(response));
        return;
    }

    ShortenRequest req;

    req.url = (*json)["url"].asString();
    req.customAlias = (*json)["customAlias"].asString();

    auto result = urlService.shortenUrl(req);

    response["success"] = result.success;
    response["shortCode"] = result.shortCode;
    response["shortUrl"] = result.shortUrl;
    response["error"] = result.error;

    callback(HttpResponse::newHttpJsonResponse(response));
}


void UrlController::redirect(
    const HttpRequestPtr& request,
    std::function<void(const HttpResponsePtr&)>&& callback,
    const std::string& code)
{
    //std::cout << "Redirect endpoint hit: " << code << std::endl;
    auto originalUrl =
        urlService.getOriginalUrl(code);

    if(!originalUrl.has_value()){
        auto resp =
            HttpResponse::newNotFoundResponse();

        callback(resp);

        return;
    }

    auto resp =
        HttpResponse::newRedirectionResponse(
            originalUrl.value());

    callback(resp);
}