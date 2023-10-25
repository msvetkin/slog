// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include <vector>
#include <utility>
#include <string>

namespace slog::core {

using Attr = std::pair<std::string, std::string>;
using Attrs = std::vector<Attr>;

} // namespace slog::core
