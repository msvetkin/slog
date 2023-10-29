// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include <string_view>
#include <source_location>

namespace slog::core {

class Context {
 public:
  template<std::size_t N>
  consteval Context(
      const char (&message)[N],
      std::source_location location = std::source_location::current()) noexcept
      : message_(&message[0]),
        location_(location) {
  }

  consteval Context(Context &&other) = default;
  consteval Context &operator=(Context &&other) = default;

  consteval Context(const Context &other) = default;
  consteval Context &operator=(const Context &other) = default;

  [[nodiscard]] std::string_view message() const noexcept {
    return message_;
  }

  [[nodiscard]] std::source_location location() const noexcept {
    return location_;
  }

 private:
  std::string_view message_;
  std::source_location location_;
};

} // namespace slog::core
