// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/slog.hpp"

#include <catch2/catch_test_macros.hpp>

namespace slog::core {

TEST_CASE("header sanity check") {
  auto logger = defaultLogger();
  (void) logger;
}


} // namespace slog::core
