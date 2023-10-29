// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include "slog/core/record.hpp"

#include <utility>

namespace slog::core {

template<typename T>
concept Handler = requires(T t) {
  { t.handle(std::declval<Record>()) } -> std::same_as<void>;
  { t.handle(std::declval<Record>(), "key", 1) } -> std::same_as<void>;
  { t.enabled(Level::Debug) } -> std::same_as<bool>;
};

} // namespace slog::core
