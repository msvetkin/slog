// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/slog.hpp"

#include <string_view>

int main(int /*argc*/, char * /*argv*/ []) {
  slog::debug("test", "age", 3);
  constexpr std::string_view name = "Mikhail";
  slog::debug("test", "age", 3, "name", name);
  return 0;
}
