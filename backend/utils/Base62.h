#pragma once

#include <cstdint>
#include <string>

class Base62{
    public:
        static std::string encode(uint64_t number);
        static uint64_t decode(const std::string& code);

    private:
        static const std::string CHARSET;
};