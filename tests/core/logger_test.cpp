// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/core/logger.hpp"

#include <catch2/catch_test_macros.hpp>

#include <optional>

namespace slog::core {

TEST_CASE("enabled") {
  Logger logger;
  REQUIRE(logger.enabled(Level::Debug));
}

// struct DummyHandler : Handler {
  // void handle(const Record &r) noexcept override {
    // record = r;
  // }

  // bool enabled(const Level) const noexcept {
    // return true;
  // }

  // std::optional<Record> record;
// };

// TEST_CASE("make") {
  // auto handler = std::make_shared<DummyHandler>();
  // auto logger = Logger::make(handler);
  // REQUIRE(logger);
// }

// TEST_CASE("debug") {
  // auto handler = std::make_shared<DummyHandler>();
  // auto logger = Logger::make(handler);
  // logger->debug("test", "age", 3);
  // REQUIRE(logger->enabled(Level::Debug));
  // REQUIRE(handler->record);
  // REQUIRE(handler->record->context.message() == std::string_view{"test"});
  // REQUIRE(handler->record->attrs == Attrs{{"age", "3"}});
// }

} // namespace slog::core
