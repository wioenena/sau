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

    [[nodiscard]] virtual inline std::size_t read(std::vector<std::uint8_t>& outBuffer) {
      return read(outBuffer.data(), outBuffer.size());
    }

    [[nodiscard]] virtual inline std::size_t read(const std::span<std::uint8_t> outBuffer) {
      return read(outBuffer.data(), outBuffer.size());
    }

    [[nodiscard]] inline std::uint8_t readByte() {
      std::uint8_t byte = 0;
      if (read(&byte, 1) != 1) {
        throw std::runtime_error("Unexpected EOF while reading byte");
      }

      return byte;
    }

    [[nodiscard]] virtual bool eof() const = 0;
  };

  class OutputStream {};
} // namespace sau

#endif // SAU_INPUT_STREAM_HPP
