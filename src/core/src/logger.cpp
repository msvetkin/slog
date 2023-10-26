// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/core/logger.hpp"

#include "slog/core/handler.hpp"

namespace slog::core {

Logger::Logger(const std::shared_ptr<Handler> &handler)
    : handler_(handler) {
}

std::expected<Logger, std::string> Logger::make(
    const std::shared_ptr<Handler> &handler) noexcept {
  if (!handler) {
    return std::unexpected{"handler is null"};
  }

  return Logger{handler};
}

// void Logger::debug(std::string message, Attrs attrs,
                   // std::source_location sl) const noexcept {
  // log2(Level::Debug, std::move(message), std::move(attrs), sl);
// }

// void Logger::info(std::string message, Attrs attrs,
                  // std::source_location sl) const noexcept {
  // log2(Level::Info, std::move(message), std::move(attrs), sl);
// }

// void Logger::warning(std::string message, Attrs attrs,
                     // std::source_location sl) const noexcept {
  // log2(Level::Warning, std::move(message), std::move(attrs), sl);
// }

// void Logger::error(std::string message, Attrs attrs,
                   // std::source_location sl) const noexcept {
  // log2(Level::Error, std::move(message), std::move(attrs), sl);
// }

void Logger::logImpl(Level level, const Context &context, Attrs attrs) const noexcept {
  handler_->handle({
      Record::Clock::now(),
      context,
      level,
      std::move(attrs),
  });
}

bool Logger::enabled(const Level level) const noexcept {
  return handler_->enabled(level);
}

}  // namespace slog::core
