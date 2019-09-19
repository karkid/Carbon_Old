#pragma once

#include "Event.h"

namespace Carbon {

    class CARBON_API EventDispatcher
    {
        NON_COPYABLE_CLASS(EventDispatcher)
        template<typename T>
        using eventCallBackFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event) : m_Event(event) {}
        template <typename T> 
        bool dispatch(eventCallBackFn<T> eventCallBack)
        {
            if (m_Event.type() == T::sType())
            {
                bool bStopPropogation = eventCallBack(*(T*)&m_Event);
                if (bStopPropogation)
                {
                    m_Event.stopEventPropogation();
                }
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };
}