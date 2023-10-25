// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/core/handler.hpp"
#include "slog/core/logger.hpp"

#include <catch2/catch_test_macros.hpp>

namespace slog::core {

struct DummyHandler : Handler {
  void handle(const Record &r) noexcept override {
    record = r;
  }

  Record record;
};

TEST_CASE("make") {
  auto handler = std::make_shared<DummyHandler>();
  auto logger = Logger::make(handler);
  REQUIRE(logger);
}

TEST_CASE("debug") {
  auto handler = std::make_shared<DummyHandler>();
  auto logger = Logger::make(handler);
  logger->debug("test", {{"1", "2"}});
  REQUIRE(handler->record.message == std::string{"test"});
  REQUIRE(handler->record.attrs == Attrs{{"1", "2"}});
}

} // namespace slog::core
