#ifndef SAU_SEEKABLE_STREAM_HPP
#define SAU_SEEKABLE_STREAM_HPP

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#include <cstddef>

namespace sau {
  class SeekableStream {
  public:
    virtual ~SeekableStream() = default;

    inline void seek(std::size_t offset) {
      m_position = offset;
    }


    [[nodiscard]] inline std::size_t tell() const {
      return m_position;
    }

  private:
    SeekableStream(const SeekableStream&) = delete;
    SeekableStream& operator=(const SeekableStream&) = delete;
    SeekableStream(SeekableStream&&) = delete;
    SeekableStream& operator=(SeekableStream&&) = delete;

  protected:
    SeekableStream() = default;
    std::size_t m_position{ 0 };
  };
} // namespace sau

#endif // SAU_SEEKABLE_STREAM_HPP
