#include "capch.h"

#include "Application.h"
#include "events/EventDispatcher.h"
#include "events/ApplicationEvent.h"


namespace Carbon {

    Application::Application() : m_bRunning(true)
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->setEventCallback(BIND_EVENT_FN(Application::onEvent));
    }

    Application::~Application()
    {
    }

    void Application::onEvent(Event & evt)
    {
        EventDispatcher dispatcher(evt);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));
    }

    bool Application::onWindowClose(WindowCloseEvent& evt)
    {
        m_bRunning = false;
        return true;
    }

    void Application::run()
    {
        AppLoadEvent appLoad;
        LOG_INFO("%s", appLoad.toString().c_str());
        while (m_bRunning)
            m_Window->onUpdate();
    }
}
