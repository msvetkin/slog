# SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
# SPDX-License-Identifier: MIT

include_guard(GLOBAL)

find_package(Catch2 CONFIG REQUIRED)

if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  find_package(slog CONFIG REQUIRED)
endif()

include(CTest)
include(Catch)

# sets all nessary default things
function(add_slog_test test_name)
  cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME module_name)

  set(test_file "${test_name}_test.cpp")
  set(test_target "${module_name}-${test_name}")

  add_executable(${test_target} "${test_file}")

  target_link_libraries(
    ${test_target} PRIVATE slog::${module_name} Catch2::Catch2WithMain
  )

  catch_discover_tests(${test_target} TEST_PREFIX "${test_target}:" ${ARGN})
endfunction()
