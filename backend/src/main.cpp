#include <drogon/drogon.h>

int main(){

    drogon::app().addListener("0.0.0.0", 8080);

    LOG_INFO << "shortzzz server starting on http://localhost:8080";

    drogon::app().run();

    return 0;
}