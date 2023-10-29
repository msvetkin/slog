// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/core/defaulthandler.hpp"

#include <fmt/format.h>
#include <fmt/color.h>
#include <fmt/chrono.h>

namespace slog::core {

namespace {

[[nodiscard]] auto styledLevel(const Record &record) noexcept {
  switch (record.level) {
    case Level::Debug:
      return fmt::styled("DEBUG", fg(fmt::color::light_gray));
    case Level::Info:
      return fmt::styled("INFO ", fg(fmt::color::green));
    case Level::Warning:
      return fmt::styled("WARN ", fg(fmt::color::yellow));
    case Level::Error:
    default:
      return fmt::styled("ERROR", fg(fmt::color::red));
  }
}

}  // namespace

void DefaultHandler::handleImpl(const Record &record) const noexcept {
  fmt::print("{:%Y/%m/%d %H/%M/%S} {} {}", record.time,
             styledLevel(record), record.context.message());
}

bool DefaultHandler::enabled(const Level /*level*/) const noexcept {
  return true;
}

}  // namespace slog::core
