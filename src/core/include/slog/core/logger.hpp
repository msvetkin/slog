// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include "slog/core/attrs.hpp"
#include "slog/core/context.hpp"
#include "slog/core/export.hpp"
#include "slog/core/level.hpp"

#include <expected>
#include <memory>
#include <source_location>
#include <string>
#include <utility>

namespace slog::core {

class Handler;

class SLOG_CORE_EXPORT Logger {
 public:
  [[nodiscard]] static std::expected<Logger, std::string> make(
      const std::shared_ptr<Handler> &handler) noexcept;

  void debug(
      std::string message, Attrs attrs,
      std::source_location sl = std::source_location::current()) const noexcept;
  void info(
      std::string message, Attrs attrs,
      std::source_location sl = std::source_location::current()) const noexcept;
  void warning(
      std::string message, Attrs attrs,
      std::source_location sl = std::source_location::current()) const noexcept;
  void error(
      std::string message, Attrs attrs,
      std::source_location sl = std::source_location::current()) const noexcept;

  template<typename ... Args>
  void log(Level level, const Context &context, Args &&...args) const noexcept {
    log2(level, std::string{context.message()}, makeAttrs(std::forward<Args>(args)...), context.location());
  }

  [[nodiscard]] bool enabled(const Level level) const noexcept;

 private:
  explicit Logger(const std::shared_ptr<Handler> &handler);

  void log2(Level level, std::string message, Attrs attrs, std::source_location sl) const noexcept;

 private:
  std::shared_ptr<Handler> handler_;
};

}  // namespace slog::core
