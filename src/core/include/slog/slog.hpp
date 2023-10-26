// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include "slog/core/context.hpp"
#include "slog/core/logger.hpp"

namespace slog {

[[nodiscard]] core::Logger SLOG_CORE_EXPORT defaultLogger() noexcept;

void SLOG_CORE_EXPORT setDefaultLogger(core::Logger logger) noexcept;

template <typename... Args>
void debug(core::Context &&context, Args &&...args) noexcept {
  defaultLogger().log(core::Level::Debug, context, std::forward<Args>(args)...);
}

template <typename... Args>
void info(core::Context &&context, Args &&...args) noexcept {
  defaultLogger().log(core::Level::Info, context, std::forward<Args>(args)...);
}

template <typename... Args>
void warning(core::Context &&context, Args &&...args) noexcept {
  defaultLogger().log(core::Level::Warning, context, std::forward<Args>(args)...);
}

template <typename... Args>
void error(core::Context &&context, Args &&...args) noexcept {
  defaultLogger().log(core::Level::Error, context, std::forward<Args>(args)...);
}

}  // namespace slog
