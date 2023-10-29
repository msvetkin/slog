// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include "slog/core/record.hpp"

#include <fmt/core.h>

#include <type_traits>

namespace slog::core {

class SLOG_CORE_EXPORT DefaultHandler {
 public:
  template<typename ... Args>
  void handle(const Record &record, Args &&...args) {
    handleImpl(record);

    (
      [](auto &&args) {
        if constexpr (std::is_bounded_array_v<std::remove_cvref_t<decltype(args)>>) {
          fmt::print("{}=", args);
        } else {
          fmt::print("{} ", args);
        }
      }(std::forward<Args>(args)),
    ...);
    fmt::print("\n");
  }

  [[nodiscard]] bool enabled(const Level /*level*/) const noexcept;

 private:
  void handleImpl(const Record &record) const noexcept;
};

}  // namespace slog::core
