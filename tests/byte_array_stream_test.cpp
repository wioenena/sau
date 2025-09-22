#include "sau/byte_array_stream.hpp"
#include <gtest/gtest.h>
#include <vector>

static const std::vector<std::uint8_t> test_buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

TEST(ByteArrayInputStream, read) {
  sau::ByteArrayInputStream stream(test_buffer);
  std::vector<std::uint8_t> readBuffer(5);
  std::vector<std::uint8_t> expected = { 0, 1, 2, 3, 4 };

  std::size_t bytesRead = stream.read(readBuffer);
  EXPECT_EQ(bytesRead, 5);

  EXPECT_EQ(readBuffer, expected);
}

TEST(ByteArrayInputStream, readWithSeek) {
  sau::ByteArrayInputStream stream(test_buffer);
  std::vector<std::uint8_t> readBuffer(6);
  std::vector<std::uint8_t> expected = { 5, 6, 7, 8, 9, 10 };

  stream.seek(5);
  std::size_t bytesRead = stream.read(readBuffer.data(), readBuffer.size());
  EXPECT_EQ(bytesRead, 6);

  EXPECT_EQ(readBuffer, expected);
}

TEST(ByteArrayInputStream, readByte) {
  sau::ByteArrayInputStream stream(test_buffer);

  EXPECT_EQ(stream.readByte(), 0);
}
