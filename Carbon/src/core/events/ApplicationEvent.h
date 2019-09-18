#pragma once

#include "Event.h"

namespace Carbon
{
    class CARBON_API AppLoadEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::AppLoad, EventCategory::App)
        AppLoadEvent() = default;
    };

    class CARBON_API AppUpdateEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::AppUpdate, EventCategory::App)
        AppUpdateEvent() = default;
    };

    class CARBON_API AppRenderEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::AppRender, EventCategory::App)
        AppRenderEvent() = default;
    };

    class CARBON_API AppRefreshEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::AppRefresh, EventCategory::App)
        AppRefreshEvent() = default;
    };
}