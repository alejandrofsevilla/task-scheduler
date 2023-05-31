#ifndef TASK_HPP
#define TASK_HPP

#include <chrono>
#include <functional>
#include <future>

struct Task {
  int id;
  bool isCanceled;
  bool isSingleShot;
  std::function<void()> work;
  std::future<void> future;
  std::chrono::milliseconds timeout;
  std::chrono::time_point<std::chrono::system_clock> deadline;
};

inline constexpr bool operator<(const Task& lhs, const Task& rhs) {
  if (lhs.deadline == rhs.deadline) {
    return lhs.id < rhs.id;
  }
  return lhs.deadline < rhs.deadline;
}

#endif
