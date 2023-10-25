// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/slog.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("header sanity check") {
  auto logger = slog::defaultLogger();
  (void) logger;
}

TEST_CASE("debug") {
  slog::debug("test msg");
}
