// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/slog.hpp"

#include <optional>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("header sanity check") {
  // auto logger = slog::defaultLogger();
  // (void) logger;
}

TEST_CASE("debug") {
  slog::debug("test msg");
}

// TEST_CASE("set default logger") {

  // struct DummyHandler : slog::core::Handler {
    // void handle(const slog::core::Record &r) noexcept override {
      // record = r;
    // }

    // bool enabled(const slog::core::Level) const noexcept {
      // return true;
    // }

    // std::optional<slog::core::Record> record;
  // };

  // auto handler = std::make_shared<DummyHandler>();
  // auto logger = slog::core::Logger::make(handler).value();
  // slog::setDefaultLogger(logger);
  // slog::debug("test msg", "age", 5);

  // REQUIRE(handler->record);
  // REQUIRE(handler->record->context.message() == std::string_view{"test msg"});
  // REQUIRE(handler->record->attrs == slog::core::Attrs{{"age", "5"}});
// }
