#pragma once

#include "core.h"

namespace Carbon {

    class CARBON_API Application
    {
    public:
        Application();
        virtual ~Application();

        virtual void run();
    };

    // Need to define in client
    Application* CreateApplication();
}
