#include <string>


namespace Encoding{
    std::string encodeBase62(uint64_t value);
    uint64_t decodeBase62(const std::string& value);
}