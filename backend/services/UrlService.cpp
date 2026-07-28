#include "UrlService.h"

#include <iostream>

UrlService::UrlService(Database& database)
    : database_(database)
{}

std::optional<std::string>
UrlService::findExistingShortCode(
    const std::string& url){
    const char* sql = "SELECT short_code FROM urls WHERE original_url = ?";

    sqlite3_stmt* stmt = nullptr;

    if(sqlite3_prepare_v2(
            database_.getConnection(),
            sql,
            -1,
            &stmt,
            nullptr) != SQLITE_OK){
        return std::nullopt;
    }

    sqlite3_bind_text(
        stmt,
        1,
        url.c_str(),
        -1,
        SQLITE_TRANSIENT);

    if(sqlite3_step(stmt) == SQLITE_ROW){
        std::string code =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt,0));

        sqlite3_finalize(stmt);

        return code;
    }

    sqlite3_finalize(stmt);

    return std::nullopt;
}


bool UrlService::aliasExists(
    const std::string& alias){
    if(alias.empty())
        return false;

    const char* sql =
        "SELECT COUNT(*) FROM urls WHERE short_code = ?";

    sqlite3_stmt* stmt = nullptr;

    sqlite3_prepare_v2(
        database_.getConnection(),
        sql,
        -1,
        &stmt,
        nullptr);

    sqlite3_bind_text(
        stmt,
        1,
        alias.c_str(),
        -1,
        SQLITE_TRANSIENT);

    bool exists=false;

    if(sqlite3_step(stmt)==SQLITE_ROW){
        exists=sqlite3_column_int(stmt,0)>0;
    }

    sqlite3_finalize(stmt);

    return exists;
}


int UrlService::insertUrl(
    const std::string& url){
        //std::cout << "insertUrl() called" << std::endl;
    const char* sql =
        "INSERT INTO urls(original_url) VALUES(?)";

    sqlite3_stmt* stmt=nullptr;

    sqlite3_prepare_v2(
        database_.getConnection(),
        sql,
        -1,
        &stmt,
        nullptr);

    sqlite3_bind_text(
        stmt,
        1,
        url.c_str(),
        -1,
        SQLITE_TRANSIENT);

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return static_cast<int>(
        sqlite3_last_insert_rowid(
            database_.getConnection()));

}


bool UrlService::updateShortCode(
    int id,
    const std::string& code){
    const char* sql =
        "UPDATE urls SET short_code=? WHERE id=?";

    sqlite3_stmt* stmt=nullptr;

    sqlite3_prepare_v2(
        database_.getConnection(),
        sql,
        -1,
        &stmt,
        nullptr);

    sqlite3_bind_text(
        stmt,
        1,
        code.c_str(),
        -1,
        SQLITE_TRANSIENT);

    sqlite3_bind_int(stmt,2,id);

    bool ok =
        sqlite3_step(stmt)==SQLITE_DONE;

        // std::cout << "updateShortCode() = "
        //   << (ok ? "SUCCESS" : "FAILED")
        //   << std::endl;

    sqlite3_finalize(stmt);

    return ok;
}


ShortenResponse UrlService::shortenUrl(
    const ShortenRequest& request){
    ShortenResponse response;

    // 1. Validate URL
    if(!UrlValidator::isValid(request.url)){
        response.success = false;
        response.error = "Invalid URL";

        return response;
    }

    // 2. Duplicate URL
    auto existing = findExistingShortCode(request.url);

    if(existing.has_value()){
        response.success = true;
        response.shortCode = existing.value();
        response.shortUrl =
            "http://localhost:8080/" + existing.value();

        return response;
    }

    // 3. Custom alias already exists
    if(!request.customAlias.empty() &&
        aliasExists(request.customAlias)){
        response.success = false;
        response.error = "Alias already exists";

        return response;
    }

    // 4. Insert URL
    int id =
        insertUrl(request.url);

    // 5. Decide final short code
    std::string code;

    if(!request.customAlias.empty()){
        code = request.customAlias;
    }
    else{
        code = Base62::encode(id);
    }

    // 6. Store generated code
    updateShortCode(id, code);

    // 7. Build response
    response.success = true;
    response.shortCode = code;
    response.shortUrl =
        "http://localhost:8080/" + code;

    return response;
}


std::optional<std::string>
UrlService::getOriginalUrl(
    const std::string& code){
    const char* sql =
        "SELECT original_url FROM urls WHERE short_code=?";

    sqlite3_stmt* stmt = nullptr;

    if(sqlite3_prepare_v2(
            database_.getConnection(),
            sql,
            -1,
            &stmt,
            nullptr) != SQLITE_OK){
        return std::nullopt;
    }

    sqlite3_bind_text(
        stmt,
        1,
        code.c_str(),
        -1,
        SQLITE_TRANSIENT);

    if(sqlite3_step(stmt) == SQLITE_ROW){
        std::string url =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt, 0));

        sqlite3_finalize(stmt);

        return url;
    }

    sqlite3_finalize(stmt);

    return std::nullopt;
}
