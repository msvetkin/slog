// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/core/context.hpp"

#include <catch2/catch_test_macros.hpp>

namespace slog::core {

TEST_CASE("ctor") {
  Context context("some message");
  const auto location = std::source_location::current();
  REQUIRE(context.message() == std::string_view{"some message"});
  REQUIRE(context.location().file_name() == location.file_name());
  REQUIRE(context.location().function_name() == location.function_name());
  REQUIRE(context.location().line() == location.line() - 1);
}

} // namespace slog::core
