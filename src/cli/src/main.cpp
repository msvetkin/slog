// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

#include "slog/slog.hpp"

// #include <fmt/core.h>
// #include <fmt/format.h>
// #include <fmt/color.h>
// #include <fmt/chrono.h>

#include <nlohmann/json.hpp>

// #include <string_view>
// #include <functional>
// #include <type_traits>
// #include <chrono>

// #include <source_location>

// namespace slog::v2 {

// class Record {
  // using Clock = std::chrono::system_clock;
  // using TimePoint = Clock::time_point;

  // TimePoint time;

  // Context context;

  // std::string_view category;

  // Level level;
// };

// auto styledLevel(const Level level) noexcept {
  // switch (level) {
    // case Level::Debug:
      // return fmt::styled("DEBUG", fg(fmt::color::light_gray));
    // case Level::Info:
      // return fmt::styled("INFO ", fg(fmt::color::green));
    // case Level::Warning:
      // return fmt::styled("WARN ", fg(fmt::color::yellow));
    // case Level::Error:
    // default:
      // return fmt::styled("ERROR", fg(fmt::color::red));
  // }
// }

// struct DefaultHandler {
  // template<typename ... Args>
  // void handle(const Level level, Context &&context, Args &&...args) {

    // const auto time = std::chrono::system_clock::now();

    // fmt::print("{:%Y/%m/%d %H/%M/%S} {} {} ", time, styledLevel(level), context.message());
    // (
      // [](auto &&args) {
        // if constexpr (std::is_bounded_array_v<std::remove_cvref_t<decltype(args)>>) {
          // fmt::print("{}=", args);
        // } else {
          // fmt::print("{} ", args);
        // }
      // }(std::forward<Args>(args)),
    // ...);
    // fmt::print("\n");
  // }

  // [[nodiscard]] bool enabled(const Level [>level<]) const noexcept {
    // return true;
  // }
// };

// template<typename T>
// concept Handler = requires(T t) {
  // { t.handle(Level::Debug, Context{"test"}) } -> std::same_as<void>;
  // { t.handle(Level::Debug, Context{"test"}, "key", 1) } -> std::same_as<void>;
  // { t.enabled(Level::Debug) } -> std::same_as<bool>;
// };

// template <typename ...>
// inline auto setHandler = DefaultHandler{};

// template <typename ... DummyArgs>
  // requires (sizeof ... (DummyArgs) == 0)
// [[nodiscard]] decltype(auto) getHandler() noexcept {
  // Handler auto &handler = setHandler<DummyArgs...>;
  // return handler;
// }

// struct Logger {
  // template<typename ... Args>
  // void debug(Context &&context, Args &&...args) const noexcept {
    // log(Level::Debug, std::move(context), std::forward<Args>(args)...);
  // }

  // template<typename ... Args, typename ... DummyArgs>
  // void log(const Level level, Context &&context, Args &&... args) const noexcept {
    // Handler auto &handler = getHandler<DummyArgs...>();

    // if (handler.enabled(level)) {
      // handler.handle(level, std::move(context), std::forward<Args>(args)...);
    // }
  // }

  // template<typename ... DummyArgs>
  // [[nodiscard]] bool enabled(const Level level) const noexcept {
    // Handler auto &handler = getHandler<DummyArgs...>();
    // return handler.enabled(level);
  // }
// };

// template<typename ... BaseArgs>
// struct LoggerWith : Logger {

  // std::tuple<BaseArgs...> with_;

  // constexpr LoggerWith(BaseArgs &&...args)
    // : with_{args...} {
  // }

  // template<typename ... Args>
  // void debug(Context &&context, Args &&...args) {
    // std::apply([&, this] (auto &&... withArgs) {
      // Logger::debug(
          // std::forward<Context>(context),
          // withArgs...,
          // std::forward<Args>(args)...);
    // }, with_);
  // }
// };

// template<typename ... Args>
// [[nodiscard]] constexpr decltype(auto) with(Args &&...args) noexcept {
  // return LoggerWith<Args...>(args...);
// }

// template<std::size_t N>
// [[nodiscard]] constexpr decltype(auto) category(const char (&category)[N]) noexcept {
  // return with("category", category);
// }

// template<typename ... Args>
// void debug(Context &&context, Args &&...args) {
  // Logger logger{};
  // logger.log(Level::Debug, std::move(context), std::forward<Args>(args)...);
// }

// } // namespace slog::v2


struct JsonHandler {
  template<typename ... Args>
  void handle(const slog::core::Record &record, Args &&...args) {
    nlohmann::json json;
    json["message"] = record.context.message();
    json["level"] = [&record] {
      switch (record.level) {
        case slog::core::Level::Debug:
          return "DEBUG";
        case slog::core::Level::Info:
          return "INFO";
        case slog::core::Level::Warning:
          return "WARN";
        case slog::core::Level::Error:
        default:
          return "ERROR";
      };
    }();

    [[maybe_unused]] const char *key = nullptr;

    (
      [&key, &json](auto &&args) mutable {
        // fmt::print("args = {}\n", args);
        if constexpr (std::is_bounded_array_v<std::remove_cvref_t<decltype(args)>>) {
          if (key) {
            json[key] = args;
            key = nullptr;
          } else {
            key = args;
          }
        } else {
          json[key] = args;
          key = nullptr;
        }
      }(std::forward<Args>(args)),
    ...);

    fmt::print("{}\n", to_string(json));
  }

  [[nodiscard]] bool enabled(const slog::core::Level /*level*/) const noexcept {
    return true;
  }
};

// template <>
// inline auto slog::core::defaultHandler<> = JsonHandler{};

void requestUrl(const std::string &url) {
  auto logger = slog::with("requestUrl", url);
  logger.debug("get", "retry", 3);
}

namespace {

constinit auto lg = slog::category("foo");

} // namespace

int main(int /*argc*/, char * /*argv*/ []) {
  slog::debug("main", "level", 10, "age", 3);

  lg.debug("test", "age", 1000);

  // slog::v2::with("level", 10)

  // slog::debug("test", "age", 3);

  // slog::v2::DefaultHandler handler;
  // handler.handle("level", 10, "age", 3);

  // JsonHandler jsonHandler;
  // slog::Handler handler = jsonHandler;
  // slog::Logger logger{handler};

  // logger.log("age", 1);

  // do_thing("age", 55);

  // constexpr std::string_view name = "Mikhail";

  // slog::debug("test", "age", 3, "name", name);
  // slog::info("test", "age", 10, "name", name);
  // slog::warning("test", "age", 35, "name", name);
  // slog::error("test", "age", 88, "name", name);


  requestUrl("https://google.com");

  return 0;
}
