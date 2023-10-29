// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include "slog/core/logger.hpp"

#include <tuple>

namespace slog {

template<typename ... BaseArgs>
struct LoggerWith : core::Logger {

  std::tuple<BaseArgs...> with_;

  constexpr LoggerWith(BaseArgs &&...args)
    : with_{args...} {
  }

  template<typename ... Args>
  void debug(const core::Context &context, Args &&...args) {
    std::apply([&, this] (auto &&... withArgs) {
      core::Logger::debug(
          context,
          withArgs...,
          std::forward<Args>(args)...);
    }, with_);
  }
};

template<typename ... Args>
[[nodiscard]] constexpr decltype(auto) with(Args &&...args) noexcept {
  return LoggerWith<Args...>(args...);
}

template<std::size_t N>
[[nodiscard]] constexpr decltype(auto) category(const char (&category)[N]) noexcept {
  return with("category", category);
}

template<typename ... Args>
void debug(const core::Context &context, Args &&...args) {
  core::Logger logger{};
  logger.log(core::Level::Debug, context, std::forward<Args>(args)...);
}

}  // namespace slog
