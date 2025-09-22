#include "sau/byte_array_stream.hpp"
#include <cassert>
#include <cstring>

namespace sau {
  [[nodiscard]] std::size_t ByteArrayInputStream::read(std::uint8_t* outBuffer, std::size_t size) {
    if (eof())
      return 0;

    const std::size_t bytesToRead = std::min(size, m_buffer.size() - m_position);
    std::memcpy(outBuffer, m_buffer.data() + m_position, bytesToRead);
    m_position += bytesToRead;
    return bytesToRead;
  }
} // namespace sau
