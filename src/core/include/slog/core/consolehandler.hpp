// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include "slog/core/handler.hpp"

namespace slog::core {

class SLOG_CORE_EXPORT ConsoleHandler : public Handler {
 public:
  void handle(const Record &record) noexcept override;
  [[nodiscard]] bool enabled(const Level level) const noexcept override;
};

}  // namespace slog::core
