#include <drogon/drogon.h>
#include <iostream>
#include "Base62.h"
#include "UrlValidator.h"

int main(){

    

    // std::cout << "===== Base62 Test =====" <<endl;
    // for (uint64_t i = 0; i <= 100; i++){
    //     std::string encoded = Base62::encode(i);
    //     uint64_t decoded = Base62::decode(encoded);

    //     std::cout<< i<< " -> "<< encoded<< " -> "<< decoded;

    //     if(i == decoded)
    //         std::cout << "  ;)";
    //     else
    //         std::cout << "  -_-";

    //     std::cout << '\n';
    // }
    //---------------------Base62 test end--------------------------

    std::cout << "=======urlValidator Test==========" <<std::endl;
    std::cout << UrlValidator::isValid("https://google.com") << std::endl;
    std::cout << UrlValidator::isValid("http://github.com") << std::endl;
    std::cout << UrlValidator::isValid("google.com") << std::endl;
    std::cout << UrlValidator::isValid("hello") << std::endl;
    std::cout << "=======urlValidator Test End==========" <<std::endl;



    drogon::app().addListener("0.0.0.0", 8080);

    LOG_INFO << "shortzzz server starting on http://localhost:8080";

    drogon::app().run();

    return 0;
}
