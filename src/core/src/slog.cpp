// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/slog.hpp"

#include "slog/core/consolehandler.hpp"

#include <atomic>

namespace slog {

namespace {

class DefaultLogger {
 public:
  DefaultLogger(DefaultLogger &&) = delete;
  DefaultLogger(const DefaultLogger &) = delete;
  DefaultLogger &operator=(DefaultLogger &&) = delete;
  DefaultLogger &operator=(const DefaultLogger &) = delete;

  static DefaultLogger &instance() {
    static DefaultLogger handler;
    return handler;
  }

  core::Logger get() const {
    return logger_;
  }

  void set(core::Logger logger) {
    logger_ = logger;
  }

 private:
  DefaultLogger() = default;

 private:
  core::Logger logger_ = core::Logger::make(std::make_shared<core::ConsoleHandler>()).value();
};

}  // namespace

[[nodiscard]] core::Logger defaultLogger() noexcept {
  return DefaultLogger::instance().get();
}

void setDefaultLogger(core::Logger logger) noexcept {
  DefaultLogger::instance().set(logger);
}

}  // namespace slog
