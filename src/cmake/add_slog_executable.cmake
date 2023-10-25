# SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
# SPDX-License-Identifier: MIT

include_guard(GLOBAL)

include(set_slog_target_properties)

# sets all nessary default things
function(add_slog_executable executable_name)
  set(executable_target slog-${executable_name})

  add_executable(${executable_target} ${ARGN})
  set_slog_target_properties(${executable_target} PRIVATE)

  if (TARGET slog)
    install(TARGETS ${executable_target} EXPORT slog-targets)
  endif()

  set(slog_executable_target
      ${executable_target}
      PARENT_SCOPE
  )
endfunction()
