#include "Database.h"

#include <iostream>
#include <stdexcept>

Database::Database(const std::string& dbPath)
    : db_(nullptr),
      dbPath_(dbPath)
{}

Database::~Database(){
    close();
}

bool Database::connect(){
    if (sqlite3_open(dbPath_.c_str(), &db_) != SQLITE_OK){
        std::cerr << "Failed to open database: "
                  << sqlite3_errmsg(db_)
                  << std::endl;

        return false;
    }

    std::cout << "SQLite connected successfully.\n";

    return true;
}

bool Database::initialize(){
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS urls
        (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            original_url TEXT NOT NULL,
            short_code TEXT UNIQUE,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );

        CREATE INDEX IF NOT EXISTS idx_original_url
        ON urls(original_url);
    )";

    char* error = nullptr;

    int rc = sqlite3_exec(
        db_,
        sql,
        nullptr,
        nullptr,
        &error);

    if (rc != SQLITE_OK){
        std::cerr << error << std::endl;

        sqlite3_free(error);

        return false;
    }

    return true;
}

bool Database::execute(const std::string& sql){
    char* error = nullptr;

    int rc = sqlite3_exec(
        db_,
        sql.c_str(),
        nullptr,
        nullptr,
        &error);

    if (rc != SQLITE_OK){
        std::cerr << error << std::endl;

        sqlite3_free(error);

        return false;
    }

    return true;
}

void Database::close(){
    if (db_){
        sqlite3_close(db_);
        db_ = nullptr;
    }
}

sqlite3* Database::getConnection() const{
    return db_;
}