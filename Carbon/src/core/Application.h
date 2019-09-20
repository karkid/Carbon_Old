#pragma once

#include "core.h"
#include "Window.h"
#include "core/events/WindowEvent.h"
#include "core/layers/LayerStack.h"

namespace Carbon {
    class Layer;
    class LayerStack;

    class CARBON_API Application
    {
    public:
        virtual ~Application();

        virtual void onEvent(Event& evt);
        virtual bool onWindowClose(WindowCloseEvent& ev);

        void pushLayer(Layer* layer);
        void pushOverLay(Layer* overLay);

        static Application& Get() { return *app; }
        inline Window& GetWindow() { return *m_Window; }

        virtual void run();
    protected:
        Application();
    private:
        bool m_bRunning;
        LayerStack m_Layers;
        std::unique_ptr<Window> m_Window;

        static Application* app;
    };

    // Need to define in client
    Application*  CreateApplication();
}
