// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include "level.hpp"
#include "context.hpp"

#include <fmt/core.h>

#include <nlohmann/json.hpp>

namespace slog::json {

struct JsonHandler {
  template<typename ... Args>
  void handle(const core::Level level, core::Context &&context, Args &&...args) {
    nlohmann::json json;
    json["message"] = context.message();
    json["level"] = [&level] {
      switch (level) {
        case Level::Debug:
          return "DEBUG";
        case Level::Info:
          return "INFO";
        case Level::Warning:
          return "WARN";
        case Level::Error:
        default:
          return "ERROR";
      };
    }();

    [[maybe_unused]] const char *key = nullptr;

    (
      [&key, &json](auto &&args) mutable {
        // fmt::print("args = {}\n", args);
        if constexpr (std::is_bounded_array_v<std::remove_cvref_t<decltype(args)>>) {
          if (key) {
            json[key] = args;
            key = nullptr;
          } else {
            key = args;
          }
        } else {
          json[key] = args;
          key = nullptr;
        }
      }(std::forward<Args>(args)),
    ...);

    fmt::print("{}\n", to_string(json));
  }

  [[nodiscard]] bool enabled(const Level /*level*/) const noexcept {
    return true;
  }
};

} // namespace slog::json
