// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/core/handler.hpp"
#include "slog/core/defaulthandler.hpp"

#include <catch2/catch_test_macros.hpp>

namespace slog::core {

TEST_CASE("header sanity check") {
  Handler auto handler = DefaultHandler{};
  (void) handler;
}

} // namespace slog::core
