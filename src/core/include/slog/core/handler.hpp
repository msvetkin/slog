// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include "slog/core/record.hpp"

namespace slog::core {

class SLOG_CORE_EXPORT Handler {
 public:
  virtual ~Handler();
  virtual void handle(const Record &record) noexcept = 0;
};

} // namespace slog::core
