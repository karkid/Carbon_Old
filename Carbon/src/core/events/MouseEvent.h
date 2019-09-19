#pragma once

#include "Event.h"

namespace Carbon
{
    class CARBON_API MouseEvent : public Event
    {
    public:
        DEFINE_EVENT_CATEGORY(EventCategory::eInput | EventCategory::eMouse)
        virtual ~MouseEvent() = default;
        int clientX() const { return m_ClientX; }
        int clientY() const { return m_ClientY; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << name() << " : (" << clientX() << "," << clientY() << ")\n";
            return ss.str();
        }
    protected:
        MouseEvent(int clientX, int clientY) : m_ClientX(clientX), m_ClientY(clientY) {}
    private:
        int m_ClientX, m_ClientY;
    };

    class CARBON_API MouseClickEvent : public MouseEvent
    {
    public:
        DEFINE_EVENT_TYPE(EventType::MouseClick)
        MouseClickEvent(int clientX, int clientY) : MouseEvent(clientX, clientY) {}
    };

    class CARBON_API MouseMoveEvent : public MouseEvent
    {
    public:
        DEFINE_EVENT_TYPE(EventType::MouseMove)
        MouseMoveEvent(int clientX, int clientY) : MouseEvent(clientX, clientY) {}
    };

    class CARBON_API MouseWheelEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::MouseWheel, EventCategory::eInput | EventCategory::eMouse)
        MouseWheelEvent(double xOffset, double yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}
        double xOffset() const { return m_XOffset; }
        double yOffset() const { return m_YOffset; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << name() << " : (" << xOffset() << "," << yOffset() << ")\n";
            return ss.str();
        }
    private:
        double m_XOffset, m_YOffset;
    };


    class CARBON_API MouseContextMenuEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::MouseContextMenu, EventCategory::eInput | EventCategory::eMouse)
        MouseContextMenuEvent() = default;
    };

    class CARBON_API MouseButtonEvent : public Event
    {
    public:
        DEFINE_EVENT_CATEGORY(EventCategory::eInput | EventCategory::eMouse)
        virtual ~MouseButtonEvent() = default;
        int button() const { return m_Button; }
        std::string toString() const override
        {
            std::stringstream ss;
            ss << name() << " : " << button() << "\n";
            return ss.str();
        }
    protected:
        MouseButtonEvent(int button) : m_Button(button) {}
    private:
        int m_Button;
    };

    class CARBON_API MouseUpEvent : public MouseButtonEvent
    {
    public:
        DEFINE_EVENT_TYPE(EventType::MouseUp)
        MouseUpEvent(int button) : MouseButtonEvent(button) {}
    };

    class CARBON_API MouseDownEvent : public MouseButtonEvent
    {
    public:
        DEFINE_EVENT_TYPE(EventType::MouseDown)
        MouseDownEvent(int button) : MouseButtonEvent(button) {}
    };
}