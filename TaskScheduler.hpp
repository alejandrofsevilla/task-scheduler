#ifndef TASK_SCHEDULER_HPP
#define TASK_SCHEDULER_HPP

#include <mutex>
#include <set>

#include "Task.hpp"

class TaskScheduler {
 public:
  TaskScheduler();
  template <class F, class... Args>
  int scheduleAt(const std::chrono::time_point<std::chrono::system_clock>& time,
                 F&& func, Args&&... args);
  template <class Rep, class Period, class F, class... Args>
  int scheduleAfter(const std::chrono::duration<Rep, Period>& timeout, F&& func,
                    Args&&... args);
  template <class Rep, class Period, class F, class... Args>
  int scheduleEvery(const std::chrono::duration<Rep, Period>& period, F&& func,
                    Args&&... args);
  void cancel(int taskId);
  void run();

 private:
  std::mutex m_mutex;
  std::set<Task> m_tasks;
  int m_nextTaskId;
};

#include "TaskScheduler.impl"

#endif
