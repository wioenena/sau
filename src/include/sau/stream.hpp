#ifndef SAU_INPUT_STREAM_HPP
#define SAU_INPUT_STREAM_HPP

#include <stdexcept>
#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif


#include <cassert>
#include <cstdint>
#include <span>
#include <vector>

namespace sau {
  class InputStream {
  private:
    InputStream(const InputStream&) = delete;
    InputStream& operator=(const InputStream&) = delete;
    InputStream(InputStream&&) = delete;
    InputStream& operator=(InputStream&&) = delete;

  protected:
    InputStream() = default;

  public:
    virtual ~InputStream() = default;

    [[nodiscard]] virtual std::size_t read(std::uint8_t* outBuffer, std::size_t size) = 0;

    [[nodiscard]] inline std::size_t read(std::vector<std::uint8_t>& outBuffer) {
      return read(outBuffer.data(), outBuffer.size());
    }

    [[nodiscard]] inline std::size_t read(const std::span<std::uint8_t> outBuffer) {
      return read(outBuffer.data(), outBuffer.size());
    }

    [[nodiscard]] inline std::uint8_t readByte() {
      std::uint8_t byte = 0;
      if (read(&byte, 1) != 1) {
        throw std::runtime_error("Unexpected EOF while reading byte");
      }

      return byte;
    }
  };

  class OutputStream {
  private:
    OutputStream(const OutputStream&) = delete;
    OutputStream& operator=(const OutputStream&) = delete;
    OutputStream(OutputStream&&) = delete;
    OutputStream& operator=(OutputStream&&) = delete;

  protected:
    OutputStream() = default;

  public:
    virtual ~OutputStream() = default;

    [[nodiscard]] virtual std::size_t write(const std::uint8_t* buffer, std::size_t size) = 0;

    [[nodiscard]] inline std::size_t write(const std::vector<std::uint8_t>& buffer) {
      return write(buffer.data(), buffer.size());
    }

    [[nodiscard]] inline std::size_t write(const std::span<const std::uint8_t> buffer) {
      return write(buffer.data(), buffer.size());
    }

    inline void writeByte(std::uint8_t byte) {
      if (write(&byte, 1) != 1) {
        throw std::runtime_error("Failed to write byte");
      }
    }
  };
} // namespace sau

#endif // SAU_INPUT_STREAM_HPP
