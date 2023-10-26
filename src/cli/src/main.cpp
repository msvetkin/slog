// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/slog.hpp"

#include <string_view>

void requestUrl(const std::string &url) {
  auto logger = slog::with("requestUrl", url);
  logger.debug("do", "retry", 3);
}

int main(int /*argc*/, char * /*argv*/ []) {
  slog::debug("test", "age", 3);

  constexpr std::string_view name = "Mikhail";

  slog::debug("test", "age", 3, "name", name);
  slog::info("test", "age", 10, "name", name);
  slog::warning("test", "age", 35, "name", name);
  slog::error("test", "age", 88, "name", name);


  requestUrl("https://google.com");

  return 0;
}
