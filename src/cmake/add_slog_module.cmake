# SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
# SPDX-License-Identifier: MIT

include_guard(GLOBAL)

include(set_slog_target_properties)

include(GenerateExportHeader)
include(GNUInstallDirs)

# generaete header with export macro
function(_slog_module_generate_export_headers target)
  set(export_file_dir "${CMAKE_CURRENT_BINARY_DIR}/include/slog")
  generate_export_header(${module_target}
    EXPORT_FILE_NAME "${export_file_dir}/${module_name}/export.hpp"
  )

  target_include_directories(
    ${module_target} ${module_type}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  )

  if (TARGET slog)
    install(DIRECTORY ${export_file_dir} TYPE INCLUDE)
  endif()
endfunction()

# sets all nessary default things
function(add_slog_module module_name)
  set(module_target slog-${module_name})
  set(module_alias slog::${module_name})

  add_library(${module_target} ${ARGN})
  add_library(${module_alias} ALIAS ${module_target})

  get_target_property(module_target_type ${module_target} TYPE)
  if("${module_target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(module_type "INTERFACE")
  else()
    set(module_type "PUBLIC")
    _slog_module_generate_export_headers(${module_target})
  endif()

  set_slog_target_properties(${module_target} ${module_type})

  target_include_directories(
    ${module_target} ${module_type}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )
  set_target_properties(${module_target} PROPERTIES EXPORT_NAME ${module_name})

  target_link_libraries(${module_target} ${module_type})

  if (TARGET slog)
    target_link_libraries(slog INTERFACE ${module_target})
    install(TARGETS ${module_target} EXPORT slog-targets)
    install(DIRECTORY include/slog TYPE INCLUDE)
  endif()

  set(slog_module_target
      ${module_target}
      PARENT_SCOPE
  )
endfunction()
