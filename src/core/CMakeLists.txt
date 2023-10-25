# SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
# SPDX-License-Identifier: MIT

add_slog_module(core)

target_sources(${slog_module_target} PRIVATE
  include/slog/core/level.hpp
  src/level.cpp)
