// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include "slog/core/export.hpp"

#include <string>

namespace slog::core {

[[nodiscard]] SLOG_CORE_EXPORT std::string version() noexcept;

} // namespace slog::core
