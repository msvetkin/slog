// SPDX-FileCopyrightText: Copyright 2023 Mikhail Svetkin
// SPDX-License-Identifier: MIT

// #include "slog/slog.hpp"
#include "slog/core/context.hpp"

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/color.h>
#include <fmt/chrono.h>

// #include <nlohmann/json.hpp>

#include <string_view>
#include <functional>
#include <type_traits>
#include <chrono>

// namespace slog {

// template<typename T>
// concept AsKeyValue = requires(T t) {
  // { t.do_thing("key", 1) } -> std::same_as<void>;
// };

// struct default_impl {
  // template<typename T>
  // void do_thing(const char *key, const T &t) {
    // fmt::print("default_impl: key = {}, value = {}\n", key, t);
  // }
// };

// template <typename ...>
// inline auto injected_interface = default_impl{};

// template<typename ... Args, typename ... DummyArgs>
  // requires (sizeof ... (DummyArgs) == 0)
// void do_thing(Args...args) {
  // AsKeyValue auto &iface = injected_interface<DummyArgs...>;
  // iface.do_thing(args...);
// }

// struct json_impl {
  // template<typename T>
  // void do_thing(const char *key, const T &t) {
    // fmt::print("json_impl: key = {}, value = {}\n", key, t);
  // }
// };


// template<typename H>
// constexpr auto ff = [] (const void *const p, auto k, auto v) {
  // static_cast<const H *const>(p)->handle(k, v);
// };

// template<typename H>
// constexpr auto ff2 = [] (const void *const self) {
  // static_cast<const H *const>(self)->handle(3, 4);
// };

// template<typename T>
// void dump() {
  // fmt::print("{}\n", __PRETTY_FUNCTION__);
// }

// struct Handler {

  // struct Caller {
        // template <typename H, typename T,typename U>
        // void operator()(H *h, T t, U u){
            // h->handle(t,u);
        // }
    // };


  // template<typename T>
  // Handler(const T &t)
      // : impl_(&t) {

    // auto cb = std::bind(Caller{}, &t, std::placeholders::_1, std::placeholders::_2);
    // cb("age", 3);
    // ff<T>(impl_, "age", 3);
    // ff2<T>(impl_);

    // dump<decltype(&ff<T>)>();
    // dump<decltype(&ff2<T>)>();
    // void(*ptr)(const void *) = +ff2<T>;
    // ptr(impl_);
    // // auto p2 = +ff<T>;
    // // p2("age", 5);
  // }

  // template<typename T>
  // void handle(const char *key, const T &value) {
    // fmt::print("Handler {{ \"{}\": {} }}\n", key, value);
  // }

  // const void *impl_{nullptr};
// };

// struct Logger {
  // Handler &handler;

  // template<typename T>
  // void log(const char *key, const T &value) {
    // fmt::print("{{ \"{}\": {} }}\n", key, value);
    // handler.handle(key, value);
    // do_thing(key, value);
  // }
// };

// } // namespace slog


// struct JsonHandler {

  // template <typename T, typename U>
  // void handle(T t, U u ) const {
    // fmt::print("handle: t = {}, u = {}\n", t, u);
  // }

// };

#include <source_location>

namespace slog::v2 {

class Context {
 public:
  template<std::size_t N>
  consteval Context(
      const char (&message)[N],
      std::source_location location = std::source_location::current()) noexcept
      : message_(&message[0]),
        location_(location) {
  }

  consteval Context(Context &&other) = default;
  consteval Context &operator=(Context &&other) = default;

  consteval Context(const Context &other) = default;
  consteval Context &operator=(const Context &other) = default;

  [[nodiscard]] std::string_view message() const noexcept {
    return message_;
  }

  [[nodiscard]] std::source_location location() const noexcept {
    return location_;
  }

 private:
  std::string_view message_;
  std::source_location location_;
};

enum class Level {
  Debug,
  Info,
  Warning,
  Error
};

auto styledLevel(const Level level) noexcept {
  switch (level) {
    case Level::Debug:
      return fmt::styled("DEBUG", fg(fmt::color::light_gray));
    case Level::Info:
      return fmt::styled("INFO ", fg(fmt::color::green));
    case Level::Warning:
      return fmt::styled("WARN ", fg(fmt::color::yellow));
    case Level::Error:
    default:
      return fmt::styled("ERROR", fg(fmt::color::red));
  }
}

struct DefaultHandler {
  template<typename ... Args>
  void handle(const Level level, Context &&context, Args &&...args) {

    const auto time = std::chrono::system_clock::now();

    fmt::print("{:%Y/%m/%d %H/%M/%S} {} {} ", time, styledLevel(level), context.message());
    (
      [](auto &&args) {
        if constexpr (std::is_bounded_array_v<std::remove_cvref_t<decltype(args)>>) {
          fmt::print("{}=", args);
        } else {
          fmt::print("{} ", args);
        }
      }(std::forward<Args>(args)),
    ...);
    fmt::print("\n");
  }

  [[nodiscard]] bool enabled(const Level /*level*/) const noexcept {
    return true;
  }
};

// struct JsonHandler {
  // template<typename ... Args>
  // void handle(Context &&context, Args &&...args) {
    // nlohmann::json json;
    // json["message"] = context.message();

    // [[maybe_unused]] const char *key = nullptr;

    // (
      // [&key, &json](auto &&args) mutable {
        // if constexpr (std::is_bounded_array_v<std::remove_cvref_t<decltype(args)>>) {
          // key = args;
        // } else {
          // json[key] = args;
        // }
      // }(std::forward<Args>(args)),
    // ...);

    // fmt::print("{}\n", to_string(json));
  // }
// };

template<typename T>
concept Handler = requires(T t) {
  { t.handle(Level::Debug, Context{"test"}) } -> std::same_as<void>;
  { t.handle(Level::Debug, Context{"test"}, "key", 1) } -> std::same_as<void>;
  { t.enabled(Level::Debug) } -> std::same_as<bool>;
};

template <typename ...>
inline auto setHandler = DefaultHandler{};

template <typename ... DummyArgs>
  requires (sizeof ... (DummyArgs) == 0)
[[nodiscard]] decltype(auto) getHandler() noexcept {
  Handler auto &handler = setHandler<DummyArgs...>;
  return handler;
}

struct Logger {
  template<typename ... Args>
  void debug(Context &&context, Args &&...args) const noexcept {
    log(Level::Debug, std::move(context), std::forward<Args>(args)...);
  }

  template<typename ... Args, typename ... DummyArgs>
  void log(const Level level, Context &&context, Args &&... args) const noexcept {
    Handler auto &handler = getHandler<DummyArgs...>();

    if (handler.enabled(level)) {
      handler.handle(level, std::move(context), std::forward<Args>(args)...);
    }
  }

  template<typename ... DummyArgs>
  [[nodiscard]] bool enabled(const Level level) const noexcept {
    Handler auto &handler = getHandler<DummyArgs...>();
    return handler.enabled(level);
  }
};

template<typename ... BaseArgs>
struct LoggerWith : Logger {

  std::tuple<BaseArgs...> with_;

  LoggerWith(BaseArgs &&...args)
    : with_{args...} {
  }

  template<typename ... Args>
  void debug(Context &&context, Args &&...args) {
    std::apply([&, this] (auto &&... withArgs) {
      Logger::debug(
          std::forward<Context>(context),
          withArgs...,
          std::forward<Args>(args)...);
    }, with_);
  }
};

template<typename ... Args>
[[nodiscard]] decltype(auto) with(Args &&...args) noexcept {
  return LoggerWith<Args...>(args...);
}

template<typename ... Args>
void debug(Context &&context, Args &&...args) {
  Logger logger{};
  logger.log(Level::Debug, std::move(context), std::forward<Args>(args)...);
}

} // namespace slog::v2

// template <>
// inline auto slog::v2::setHandler<> = slog::v2::JsonHandler{};

void requestUrl(const std::string &url) {
  auto logger = slog::v2::with("requestUrl", url);
  logger.debug("get", "retry", 3);
}

int main(int /*argc*/, char * /*argv*/ []) {
  slog::v2::debug("main", "level", 10, "age", 3);

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
