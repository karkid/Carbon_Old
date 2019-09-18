#pragma once

#include "Event.h"

namespace Carbon
{
    class CARBON_API WindowCreateEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::WindowCreate, EventCategory::Window)
        WindowCreateEvent() = default;
    };

    class CARBON_API WindowDestroyEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::WindowDestroy, EventCategory::Window)
        WindowDestroyEvent() = default;
    };

    class CARBON_API WindowOpenEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::WindowOpen, EventCategory::Window)
        WindowOpenEvent() = default;
    };

    class CARBON_API WindowCloseEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::WindowClose, EventCategory::Window)
        WindowCloseEvent() = default;
    };

    class CARBON_API WindowFocuseEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::WindowFocus, EventCategory::Window)
        WindowFocuseEvent() = default;
    };

    class CARBON_API WindowBlurEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::WindowBlur, EventCategory::Window)
        WindowBlurEvent() = default;
    };

    class CARBON_API WindowResizeEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::WindowResize, EventCategory::Window)
        WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {};
        unsigned int height() const { return m_Height; }
        unsigned int width() const { return m_Width; }
        std::string toString() const override
        {
            std::stringstream ss;
            ss << name() << " : (" << height() << "," << width() << ")\n";
            return ss.str();
        }
    private:
        unsigned int m_Width, m_Height;
    };

    class CARBON_API WindowMovedEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::WindowMoved, EventCategory::Window)
        WindowMovedEvent(int xPosition, int yPosition) : m_XPosition(xPosition), m_YPosition(yPosition) {};
        int xPosition() const { return m_XPosition; }
        int yPosition() const { return m_YPosition; }
        std::string toString() const override
        {
            std::stringstream ss;
            ss << name() << " : (" << xPosition() << "," << yPosition() << ")\n";
            return ss.str();
        }
    private:
        int m_XPosition, m_YPosition;
    };
}