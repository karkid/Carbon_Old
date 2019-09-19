#pragma once

#include "core.h"
#include "Window.h"
#include "events/WindowEvent.h"

namespace Carbon {

    class CARBON_API Application
    {
    public:
        virtual ~Application();

        virtual void onEvent(Event& evt);
        virtual bool onWindowClose(WindowCloseEvent& ev);

        virtual void run();
    protected:
        Application();
    private:
        bool m_bRunning;
        std::unique_ptr<Window> m_Window;
    };

    // Need to define in client
    Application*  CreateApplication();
}
