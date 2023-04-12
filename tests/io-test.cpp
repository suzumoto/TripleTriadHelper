#include <io-util.hpp>
#include <gtest/gtest.h>

TEST(ioTest, CASE1){
  io_util io;
  EXPECT_EQ(io.cardnum_to_id["6545"], Vysage);
  EXPECT_EQ(io.cardnum_to_id["4a2a"], Rinoa);
  EXPECT_EQ(io.cardnum_to_id["31aa"], Doomtrain);
  
}
