// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/slog.hpp"

int main(int /*argc*/, char * /*argv*/ []) {
  slog::debug("test", "age", 3);
  return 0;
}
