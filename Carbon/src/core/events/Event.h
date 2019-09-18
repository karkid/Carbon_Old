#pragma once

#include "capch.h"
#include "core/core.h"

namespace Carbon
{
    enum class EventType
    {
        None = 0,
        /* App */
        AppLoad, AppUpdate, AppRender, AppRefresh,
        /* Window */
        WindowCreate, WindowDestroy, WindowOpen, WindowClose, WindowResize, WindowFocus, WindowBlur, WindowMoved,
        /* Keybord */
        KeyPressed, KeyReleased,
        /* Mouse */
        MouseClick, MouseContextMenu, MouseUp, MouseDown, MouseWheel, MouseMove,
    };

    enum EventCategory
    {
        None        = 0,
        App         = Bit(0),
        Window      = Bit(1),
        Input       = Bit(2),
        Keyboard    = Bit(3),
        Mouse       = Bit(4),
    };

    #define DEFINE_EVENT_CATEGORY(evtCategory) int category() const override { return evtCategory; }
    #define DEFINE_EVENT_TYPE(evtType) \
        static  EventType sType() { return evtType; } \
        virtual EventType type() const override { return sType(); } \
        virtual const char* name() const override { return #evtType; }

    #define DEFINE_EVENT(type, category) \
        DEFINE_EVENT_CATEGORY(category) \
        DEFINE_EVENT_TYPE(type)

    class CARBON_API Event
    {
    public:
        virtual ~Event() = default;
        virtual EventType type() const = 0;
        virtual const char* name() const = 0;
        virtual int category() const = 0;
        virtual std::string toString() const { return name(); }

        inline bool belongsTo(EventCategory evCategory) { return this->category() & evCategory; }
        inline void stopEventPropogation() { m_bHandel = true; }
        inline bool handeled() { return m_bHandel; }
    protected:
        Event() : m_bHandel(false) {}
    private:
        bool m_bHandel;
    };
}