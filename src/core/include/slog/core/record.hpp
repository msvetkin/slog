// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include "slog/core/attrs.hpp"
#include "slog/core/context.hpp"
#include "slog/core/export.hpp"
#include "slog/core/level.hpp"

#include <chrono>
#include <source_location>
#include <string>
#include <utility>
#include <vector>

namespace slog::core {

struct SLOG_CORE_EXPORT Record {
  using Clock = std::chrono::system_clock;
  using TimePoint = Clock::time_point;

  TimePoint time;

  Context context;

  Level level;

  Attrs attrs;
};

}  // namespace slog::core
