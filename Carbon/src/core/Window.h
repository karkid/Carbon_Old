#pragma once

#include "capch.h"
#include "core.h"
#include "events/Event.h"

namespace Carbon 
{
    struct WindowProps
    {
        std::string title;
        unsigned int width;
        unsigned int height;
        WindowProps(const std::string& sTitle = "Carbon", unsigned int iWidth = 1280, unsigned int iHeight = 720)
            : title(sTitle), width(iWidth), height(iHeight)
        {
        }
    };

    class CARBON_API Window
    {
    public:
        using  EventCallBackFn = std::function<void(Event&)>;
        virtual ~Window() = default;

        virtual void onUpdate() = 0;
        virtual unsigned int width() const = 0;
        virtual unsigned int height() const = 0;

        virtual void setEventCallback(const EventCallBackFn& callbackFn) = 0;
        virtual void setVSync(bool enabled) = 0;
        virtual bool isVSync() const = 0;

        virtual void* nativeWindow() = 0;
        virtual void  clearWindow() = 0;

        static Window* Create(const WindowProps& props = WindowProps());
    protected:
        Window() = default;
    };
}