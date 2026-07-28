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
        "SELECT COUNT(*) FROM urls WHERE custom_alias = ?";

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
    const std::string& url,
    const std::string& alias){
    const char* sql =
        "INSERT INTO urls(original_url,custom_alias)"
        "VALUES(?,?)";

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

    if(alias.empty())
        sqlite3_bind_null(stmt,2);
    else
        sqlite3_bind_text(
            stmt,
            2,
            alias.c_str(),
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

    sqlite3_finalize(stmt);

    return ok;
}