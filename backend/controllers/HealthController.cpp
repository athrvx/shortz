#include "HealthController.h"

using namespace drogon;

void HealthController::health(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    Json::Value response;

    response["status"] = "ok";
    response["service"] = "shortz";
    response["version"] = "1.0.0";

    auto resp = HttpResponse::newHttpJsonResponse(response);

    callback(resp);
}