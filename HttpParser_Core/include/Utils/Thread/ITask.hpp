#pragma once

#include "../Foundation.hpp"

namespace greatbridf
{

    struct ITask : public virtual Interface
    {
        ~ITask() override = default;
        virtual void run() = 0;
    };

}