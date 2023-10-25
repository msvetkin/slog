# SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
# SPDX-License-Identifier: MIT

add_slog_executable(cli)

target_sources(${slog_executable_target} PRIVATE src/main.cpp)

target_link_libraries(${slog_executable_target}
  PRIVATE
    slog::core
)
