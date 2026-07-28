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

    std::cout << "Database initialized.\n";

    //-------

    sqlite3_stmt* stmt = nullptr;

    const char* sql = "SELECT id, original_url, short_code FROM urls;";

    sqlite3_prepare_v2(
        database.getConnection(),
        sql,
        -1,
        &stmt,
        nullptr);

    std::cout << "\n===== DATABASE =====\n";

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::cout
            << sqlite3_column_int(stmt, 0)
            << " | "
            << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))
            << " | ";

        auto code = sqlite3_column_text(stmt, 2);

        if (code)
            std::cout << reinterpret_cast<const char*>(code);

        std::cout << std::endl;
    }

    sqlite3_finalize(stmt);

    std::cout << "====================\n";


    //-------




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
