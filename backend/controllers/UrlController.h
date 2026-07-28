#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class UrlController : public HttpController<UrlController>
{
public:

    METHOD_LIST_BEGIN

    ADD_METHOD_TO(
        UrlController::shorten,
        "/shorten",
        Post);

    ADD_METHOD_TO(
    UrlController::redirect,
    "/{1}",
    Get);

    METHOD_LIST_END

    void shorten(
        const HttpRequestPtr& request,
        std::function<void(const HttpResponsePtr&)>&& callback);

    void redirect(
        const HttpRequestPtr& request,
        std::function<void(const HttpResponsePtr&)>&& callback,
        const std::string& code);
};