// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include "slog/core/context.hpp"
#include "slog/core/defaulthandler.hpp"
#include "slog/core/handler.hpp"

#include <utility>

namespace slog::core {

template <typename ...>
inline auto defaultHandler = DefaultHandler{};

class SLOG_CORE_EXPORT Logger {
 public:
  template<typename ... Args>
  void debug(const Context &context, Args &&...args) const noexcept {
    log(Level::Debug, std::move(context), std::forward<Args>(args)...);
  }

  template<typename ... Args>
  void info(const Context &context, Args &&...args) const noexcept {
    log(Level::Info, context, std::forward<Args>(args)...);
  }

  template<typename ... Args>
  void warning(const Context &context, Args &&...args) const noexcept {
    log(Level::Warning, context, std::forward<Args>(args)...);
  }

  template<typename ... Args>
  void error(const Context &context, Args &&...args) const noexcept {
    log(Level::Error, context, std::forward<Args>(args)...);
  }

  template<typename ... Args, typename ... DummyArgs>
  void log(const Level level, const Context &context, Args &&... args) const noexcept {
    Handler auto &handler = defaultHandler<DummyArgs...>;

    if (handler.enabled(level)) {
      handler.handle(
          { Record::Clock::now(), context, level },
          std::forward<Args>(args)...);
    }
  }

  template<typename ... DummyArgs>
  [[nodiscard]] bool enabled(const Level level) const noexcept {
    Handler auto &handler = defaultHandler<DummyArgs...>;
    return handler.enabled(level);
  }
};

}  // namespace slog::core
