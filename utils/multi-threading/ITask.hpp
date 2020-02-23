#pragma once

namespace greatbridf {

  struct ITask {
    virtual ~ITask() {};
    virtual void run() = 0;
  };

}