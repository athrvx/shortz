#include <gtest/gtest.h>
#include "../utils/Base62.h"

TEST(Base62Tests, EncodeZero){
    EXPECT_EQ(Base62::encode(0), "0");
}

TEST(Base62Tests, EncodeOne){
    EXPECT_EQ(Base62::encode(1), "1");
}

TEST(Base62Tests, DecodeZero){
    EXPECT_EQ(Base62::decode("0"), 0);
}

TEST(Base62Tests, DecodeOne){
    EXPECT_EQ(Base62::decode("1"), 1);
}

TEST(Base62Tests, EncodeDecode){
    for (uint64_t i = 0; i < 10000; i++){
        EXPECT_EQ(
            Base62::decode(
                Base62::encode(i)),
            i);
    }
}