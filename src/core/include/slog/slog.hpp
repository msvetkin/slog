// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include "slog/core/logger.hpp"
#include "slog/core/handler.hpp"

namespace slog::core {

// namespace detail {

// void CXX_SLOG_EXPORT debug(Context &&context, Attrs attrs) noexcept;

// }  // namespace detail

[[nodiscard]] Logger SLOG_CORE_EXPORT defaultLogger() noexcept;

// template <typename... Args>
// void debug(Context &&context, Args &&...args) noexcept {
  // detail::debug(std::move(context), makeAttrs(std::forward<Args>(args)...));
// }

// void CXX_SLOG_EXPORT
// info(std::string message, Attrs attrs,
     // std::source_location sl = std::source_location::current()) noexcept;

// void CXX_SLOG_EXPORT
// warning(std::string message, Attrs attrs,
        // std::source_location sl = std::source_location::current()) noexcept;

// void CXX_SLOG_EXPORT
// error(std::string message, Attrs attrs,
      // std::source_location sl = std::source_location::current()) noexcept;

}  // namespace slog::core
