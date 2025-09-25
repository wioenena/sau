#ifndef SAU_BYTE_ARRAY_STREAM_HPP
#define SAU_BYTE_ARRAY_STREAM_HPP

#include <cstring>
#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#include <cassert>
#include <vector>

#include "sau/seekable_stream.hpp"
#include "sau/stream.hpp"

namespace sau {
  class ByteArrayInputStream : public InputStream, public SeekableStream {
  private:
    const std::vector<std::uint8_t>& m_buffer;

  public:
    using InputStream::read;
    explicit ByteArrayInputStream(const std::vector<std::uint8_t>& buffer) : m_buffer(buffer) {
      assert(!m_buffer.empty());
    }

    [[nodiscard]] std::size_t read(std::uint8_t* outBuffer, std::size_t size) override;

    [[nodiscard]] inline bool eof() const override {
      return m_position >= m_buffer.size();
    }
  };

  class ByteArrayOutputStream : public OutputStream, public SeekableStream {
  private:
    std::vector<std::uint8_t>& m_buffer;

  public:
    using OutputStream::write;
    explicit ByteArrayOutputStream(std::vector<std::uint8_t>& buffer) : m_buffer(buffer) {
      assert(!m_buffer.empty());
    }


    [[nodiscard]] std::size_t write(const std::uint8_t* buffer, std::size_t size) override;

    [[nodiscard]] inline bool eof() const override {
      return m_position >= m_buffer.size();
    }
  };
} // namespace sau

#endif // SAU_BYTE_ARRAY_STREAM_HPP
