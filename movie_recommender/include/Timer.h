#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <string>

namespace Perf
{
  static constexpr bool TIMER_ENABLED = true; 

  class Timer
  {
  private:
    std::chrono::high_resolution_clock::time_point start;
    std::string label;

  public:
    explicit Timer(const std::string &label)
        : start(std::chrono::high_resolution_clock::now()), label(label)
    {
    }

    ~Timer()
    {
      if (!TIMER_ENABLED)
      {
        return;
      }

      auto end = std::chrono::high_resolution_clock::now();
      auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

      std::cerr << "[TIMER] " << label << ": "
                << us.count() << " us" << std::endl;
    }
  };
}

#endif