#include <drogon/drogon.h>
#include <iostream>
#include "Base62.h"
#include "UrlValidator.h"
#include "Database.h"

#include "../services/UrlService.h"


Database database("shortz.db");
UrlService urlService(database);


int main(){

    if (!database.connect()){
        return 1;
    }

    if (!database.initialize()){
        return 1;
    }

    //std::cout << "Database initialized.\n";

    drogon::app().addListener("0.0.0.0", 8080);

    LOG_INFO << "shortzzz server starting on http://localhost:8080";

    drogon::app().registerPostHandlingAdvice(
    [](const drogon::HttpRequestPtr&,
       const drogon::HttpResponsePtr& response)
    {
        response->addHeader(
            "Access-Control-Allow-Origin",
            "*");

        response->addHeader(
            "Access-Control-Allow-Headers",
            "Content-Type");

        response->addHeader(
            "Access-Control-Allow-Methods",
            "GET,POST,OPTIONS");
    });

    drogon::app().run();

    return 0;
}
