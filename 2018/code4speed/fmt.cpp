struct NeverTrace {
  template <typename... Args>
  void operator()(const char* format,
    Args&&... args) {}
};

struct AlwaysTrace {
  template <typename... Args>
  void operator()(const char* format,
    Args&&... args) {
      fmt::printf(format,
        std::forward<Args>(args)...);
  }
};
