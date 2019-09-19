#pragma once

#include "Event.h"

namespace Carbon 
{
    class CARBON_API KeyEvent : public Event
    {
    public:
        DEFINE_EVENT_CATEGORY(EventCategory::eInput | EventCategory::eKeyboard)
        virtual ~KeyEvent() = default;
        inline int keyCode() const { return this->m_KeyCode;  }
    protected:
        KeyEvent(int keyCode) : m_KeyCode(keyCode) {}
    private:
        int m_KeyCode;
    };

    class CARBON_API KeyPressedEvent : public KeyEvent
    {
    public:
        DEFINE_EVENT_TYPE(EventType::KeyPressed)
        KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount) {}
        inline int repeatCount() const { return m_RepeatCount; }
        std::string toString() const override
        {
            std::stringstream ss;
            ss << name() << ": " << keyCode() << "(" << repeatCount() << ")\n";
            return ss.str();
        }
    private:
        int m_RepeatCount;
    };

    class CARBON_API KeyReleasedEvent : public KeyEvent
    {
    public:
        DEFINE_EVENT_TYPE(EventType::KeyReleased)
        KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}
        std::string toString() const override
        {
            std::stringstream ss;
            ss << name() << ": " << keyCode() << "\n";
            return ss.str();
        }
    };
}