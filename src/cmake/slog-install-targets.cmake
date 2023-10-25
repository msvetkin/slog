# SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
# SPDX-License-Identifier: MIT

include_guard(GLOBAL)

include(GNUInstallDirs)

add_library(slog INTERFACE)
add_library(slog::slog ALIAS slog)
install(TARGETS slog EXPORT slog-targets)

export(EXPORT slog-targets NAMESPACE slog::)
configure_file("cmake/slog-config.cmake" "." COPYONLY)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  slog-config-version.cmake COMPATIBILITY SameMajorVersion
)

install(
  EXPORT slog-targets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/slog
  NAMESPACE slog::
)

install(
  FILES cmake/slog-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/slog-config-version.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/slog
)

