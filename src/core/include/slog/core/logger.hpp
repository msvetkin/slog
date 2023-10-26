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

  template<typename ... Args>
  void debug(const Context &context, Args &&...args) const noexcept {
    log(Level::Debug, context, std::forward<Args>(args)...);
  }

  template<typename ... Args>
  void info(const Context &context, Args &&...args) const noexcept {
    log(Level::Info, context, std::forward<Args>(args)...);
  }

  template<typename ... Args>
  void warning(Level level, const Context &context, Args &&...args) const noexcept {
    log(Level::Warning, context, std::forward<Args>(args)...);
  }

  template<typename ... Args>
  void error(Level level, const Context &context, Args &&...args) const noexcept {
    log(Level::Error, context, std::forward<Args>(args)...);
  }

  template<typename ... Args>
  void log(Level level, const Context &context, Args &&...args) const noexcept {
    if (enabled(level)) {
      logImpl(level, context, makeAttrs(std::forward<Args>(args)...));
    }
  }

  [[nodiscard]] bool enabled(const Level level) const noexcept;

 private:
  explicit Logger(const std::shared_ptr<Handler> &handler);

  void logImpl(Level level, const Context &context, Attrs attrs) const noexcept;

 private:
  std::shared_ptr<Handler> handler_;
};

}  // namespace slog::core
