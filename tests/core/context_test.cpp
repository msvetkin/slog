// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/core/context.hpp"

#include <catch2/catch_test_macros.hpp>

namespace slog::core {

TEST_CASE("ctor") {
  Context context("some message");
  REQUIRE(context.message() == std::string_view{"some message"});
}

} // namespace slog::core
