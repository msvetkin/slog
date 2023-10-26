// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#pragma once

#include "slog/core/export.hpp"

#include <vector>
#include <utility>
#include <string>
#include <type_traits>
#include <concepts>

#include <fmt/format.h>

namespace slog::core {

namespace detail {

template <typename Key, typename K = std::remove_cvref_t<Key>>
concept AsKey = requires {
  requires std::is_bounded_array_v<K>;
  requires std::same_as<std::remove_extent_t<K>, char>;
};

template <typename Value>
concept AsValue = requires {
  typename fmt::is_formattable<Value>;
};

template <typename Key, typename Value>
concept AsKeyAndValue = requires {
  requires AsKey<Key>;
  requires AsValue<Value>;
};

template <typename... Args>
struct AsAttrs;

template <typename Key, typename Value, typename... Args>
struct AsAttrs<Key, Value, Args...> {
  static constexpr bool value =
      AsKeyAndValue<Key, Value> && AsAttrs<Args...>::value;
};

template <>
struct AsAttrs<> {
  static constexpr bool value = true;
};

}  // namespace detail

template <typename... Args>
concept AsAttrs = detail::AsAttrs<Args...>::value;

struct SLOG_CORE_EXPORT Attr {
  const char *key;
  std::string value;

  // friend auto operator<=>(const Attr &) = default;
  bool operator==(const Attr&) const = default;
};

using Attrs = std::vector<Attr>;

template <typename... Args>
[[nodiscard]] Attrs makeAttrs(Args &&...args) noexcept {
  static_assert(AsAttrs<Args...>, "hmmm.....");

  Attrs attrs;
  attrs.reserve(sizeof...(args) / 2);

  [[maybe_unused]] const char *key = nullptr;

  (
    [&]() {
      if constexpr (detail::AsKey<Args>) {
        key = args;
      } else {
        attrs.emplace_back(key, fmt::to_string(args));
      }
    }(),
  ...);

  return attrs;
}

} // namespace slog::core
