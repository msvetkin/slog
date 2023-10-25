// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/slog.hpp"

#include "slog/core/consolehandler.hpp"

namespace slog::core {

namespace {

[[nodiscard]] Logger makeDefaultLogger() noexcept {
  auto logger = Logger::make(std::make_shared<ConsoleHandler>());
  return std::move(logger).value();

  // return Logger::make(std::make_shared<ConsoleHandler>())
  // .and_then([] (auto &&logger) {
  // return logger;
  // })
  // .or_else([] {
  // std::terminate();
  // });
}

}  // namespace

[[nodiscard]] Logger defaultLogger() noexcept {
  static auto logger = makeDefaultLogger();
  return logger;
}

// namespace detail {

// void debug(Context &&context, Attrs attrs) noexcept {
  // defaultLogger().log(Level::Debug, context.message(), std::move(attrs),
                      // context.location());
// }

// }  // namespace detail

// void info(std::string message, Attrs attrs, std::source_location sl) noexcept {
  // defaultLogger().log(Level::Info, std::move(message), std::move(attrs), sl);
// }

// void warning(std::string message, Attrs attrs,
             // std::source_location sl) noexcept {
  // defaultLogger().log(Level::Warning, std::move(message), std::move(attrs), sl);
// }

// void error(std::string message, Attrs attrs, std::source_location sl) noexcept {
  // defaultLogger().log(Level::Error, std::move(message), std::move(attrs), sl);
// }

}  // namespace slog::core
