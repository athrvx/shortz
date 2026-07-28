#include <gtest/gtest.h>
#include "../utils/UrlValidator.h"

TEST(UrlValidatorTests, ValidHttps){
    EXPECT_TRUE(
        UrlValidator::isValid(
            "https://google.com"));
}

TEST(UrlValidatorTests, ValidHttp){
    EXPECT_TRUE(
        UrlValidator::isValid(
            "http://github.com"));
}

TEST(UrlValidatorTests, InvalidNoProtocol){
    EXPECT_FALSE(
        UrlValidator::isValid(
            "google.com"));
}

TEST(UrlValidatorTests, InvalidText){
    EXPECT_FALSE(
        UrlValidator::isValid(
            "hello"));
}