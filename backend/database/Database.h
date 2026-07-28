#pragma once

#include <sqlite3.h>
#include <string>

class Database{
    public:
       explicit Database(const std::string& dbPath);
        ~Database();

        bool connect();

        bool initialize();

        void close();

        bool execute(const std::string& sql);

        sqlite3* getConnection() const;

    private:
        sqlite3* db_;
        std::string dbPath_;
};