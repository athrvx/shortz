#include "Base62.h"
#include <stdexcept>
#include <string>

const std::string Base62::CHARSET = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

std::string Base62::encode(uint64_t number){
    if(number == 0)
        return "0";

    std::string result;

    while(number > 0){
        result = CHARSET[number%62] + result;
        number /= 62;
    }
  return result;
}


uint64_t Base62::decode(const std::string& code){
    uint64_t number = 0;

    for(char c : code){
        size_t index = CHARSET.find(c);

        if(index == std::string::npos)
            throw std::invalid_argument("Invalid Base62 character.");

        number = number*62 + index;
    }
  return number;
}