#include "TaskScheduler.hpp"

#include <thread>

TaskScheduler::TaskScheduler() : m_mutex{}, m_tasks{}, m_nextTaskId{0} {}

void TaskScheduler::run() {
  while (!m_tasks.empty()) {
    auto earliest{m_tasks.begin()};
    if (std::chrono::system_clock::now() > earliest->deadline) {
      std::lock_guard<std::mutex> guard{m_mutex};
      auto node{m_tasks.extract(earliest)};
      auto& task{node.value()};
      if (!task.isCanceled) {
        task.isCanceled = task.isSingleShot;
        task.deadline += task.timeout;
        task.future = std::async(std::launch::async, task.work);
        m_tasks.insert(std::move(node));
      }
    }
  }
}
void TaskScheduler::cancel(int taskId) {
  std::lock_guard<std::mutex> guard{m_mutex};
  auto it{std::find_if(m_tasks.begin(), m_tasks.end(),
                       [taskId](const auto& t) { return t.id == taskId; })};
  auto node{m_tasks.extract(it)};
  auto& task{node.value()};
  task.isCanceled = true;
  m_tasks.insert(std::move(node));
}
