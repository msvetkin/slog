// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include "slog/core/export.hpp"

#include <string_view>
#include <source_location>

namespace slog::core {

class SLOG_CORE_EXPORT Context {
 public:
  template<std::size_t N>
  constexpr Context(
      const char (&message)[N],
      std::source_location location = std::source_location::current()) noexcept
      : message_(&message[0]),
        location_(location) {
  }

  constexpr Context(Context &&other) = default;
  constexpr Context &operator=(Context &&other) = default;

  constexpr Context(const Context &other) = default;
  constexpr Context &operator=(const Context &other) = default;

  [[nodiscard]] constexpr std::string_view message() const noexcept {
    return message_;
  }

  [[nodiscard]] constexpr std::source_location location() const noexcept {
    return location_;
  }

 private:
  std::string_view message_;
  std::source_location location_;
};

}  // namespace slog::core
