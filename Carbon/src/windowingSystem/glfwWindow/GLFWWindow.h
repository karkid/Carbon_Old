#pragma once

#include "core/Window.h"

struct GLFWwindow;

namespace Carbon
{
    class GLFWWindow : public Window
    {
    public:
        GLFWWindow(const WindowProps& props);
        ~GLFWWindow();

        void onUpdate() override;
        unsigned int width() const override;
        unsigned int height() const override;

        void setEventCallback(const EventCallBackFn& callbackFn) override;
        void setVSync(bool enabled) override;
        bool isVSync() const override;

        void* nativeWindow() override;
        void  clearWindow() override;

    protected:
        virtual void init(const WindowProps& props);
        virtual void shutDown();

        //Evnet handeler
        static void onWindowClose(GLFWwindow* window);
        static void onWindowFocus(GLFWwindow* window, int focusIn);
        static void onWindowSize(GLFWwindow* window, int width, int height);
        static void onKey(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
        static void onScroll(GLFWwindow* window, double xOffset, double yOffset);

    private:
        GLFWwindow* m_Window;
        struct WindowData
        {
            std::string title;
            unsigned int width;
            unsigned int height;
            bool bVSyc;
            EventCallBackFn eventCallBack;
        };
        WindowData m_Data;
    };
}

