#include "capch.h"
#include "Application.h"
#include "events/ApplicationEvent.h"

namespace Carbon {

    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::run()
    {
        AppLoadEvent appLoad;
        LOG_INFO("%s", appLoad.toString().c_str());
        while (true);
    }
}

