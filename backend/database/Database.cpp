#include "Database.h"
#include <iostream>

Database::Database(const std::string& dbPath)
    : db_(nullptr), dbPath_(dbPath){
}

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

void Database::close(){
    if (db_)
    {
        sqlite3_close(db_);
        db_ = nullptr;
    }
}

sqlite3* Database::getConnection() const{
    return db_;
}