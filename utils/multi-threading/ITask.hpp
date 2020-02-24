#pragma once

namespace greatbridf {

  struct ITask {
    virtual ~ITask() = default;
    virtual void run() = 0;
  };

}