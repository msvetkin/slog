// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/core/consolehandler.hpp"

#include "slog/core/record.hpp"

#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>

#include <chrono>
#include <functional>

template <>
struct fmt::formatter<slog::core::Attr> {
  constexpr auto parse(format_parse_context& ctx)
      -> format_parse_context::iterator {
    return ctx.begin();
  }

  auto format(const slog::core::Attr& attr, format_context& ctx) const
      -> format_context::iterator {
    return fmt::format_to(ctx.out(), "{}={}", attr.key, attr.value);
  }
};

namespace slog::core {

namespace {

auto styledLevel(const Record& record) noexcept {
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

void ConsoleHandler::handle(const Record& record) noexcept {
  fmt::print("{:%Y/%m/%d %H/%M/%S} {} {} {}\n", record.time,
             styledLevel(record), record.context.message(), fmt::join(record.attrs, " "));
}

bool ConsoleHandler::enabled(const Level) const noexcept {
  return true;
}

}  // namespace slog::core
