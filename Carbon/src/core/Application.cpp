#include "capch.h"

#include "Application.h"
#include "core/events/EventDispatcher.h"
#include "core/events/ApplicationEvent.h"
#include "core/layers/Layer.h"


namespace Carbon {
    Application* Application::app = nullptr;

    Application::Application() : m_bRunning(true)
    {
        app = this;
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

    void Application::pushLayer(Layer * layer)
    {
        m_Layers.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverLay(Layer * overLay)
    {
        m_Layers.pushOverLay(overLay);
        overLay->onAttach();
    }

    void Application::run()
    {
        AppLoadEvent appLoad;
        LOG_INFO("%s", appLoad.toString().c_str());
        while (m_bRunning)
        {
            m_Window->onUpdate();

            for (auto layer : m_Layers)
            {
                layer->onUpdate();
            }
        }
    }
}
