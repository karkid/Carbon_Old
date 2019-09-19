#pragma once

#include "Event.h"

namespace Carbon
{
    class CARBON_API AppLoadEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::AppLoad, EventCategory::eApplication)
        AppLoadEvent() = default;
    };

    class CARBON_API AppUpdateEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::AppUpdate, EventCategory::eApplication)
        AppUpdateEvent() = default;
    };

    class CARBON_API AppRenderEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::AppRender, EventCategory::eApplication)
        AppRenderEvent() = default;
    };

    class CARBON_API AppRefreshEvent : public Event
    {
    public:
        DEFINE_EVENT(EventType::AppRefresh, EventCategory::eApplication)
        AppRefreshEvent() = default;
    };
}