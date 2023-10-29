# SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
# SPDX-License-Identifier: MIT

add_slog_module(core)

target_sources(${slog_module_target}
  PRIVATE
    include/slog/core/defaulthandler.hpp
    include/slog/core/context.hpp
    include/slog/core/handler.hpp
    include/slog/core/level.hpp
    include/slog/core/logger.hpp
    include/slog/core/record.hpp
    include/slog/slog.hpp
    src/defaulthandler.cpp
    # src/handler.cpp
    # src/logger.cpp
    # src/slog.cpp
)

find_package(fmt CONFIG REQUIRED)

target_link_libraries(${slog_module_target}
  PUBLIC
    fmt::fmt
)
