#pragma once

#include "capch.h"
#include "core/core.h"
#include "core/events/Event.h"

namespace Carbon
{
    class CARBON_API Layer
    {
    public:
        virtual ~Layer() = default;

        virtual void onAttach() {};
        virtual void onDetach() {};
        virtual void onUpdate() {};
        virtual void onEvent(Event& ev) {};

        inline const std::string name() const { return m_sName; }
    protected:
        Layer(std::string sName = "Layer") : m_sName(sName) {}
    private:
        std::string m_sName;
    };
}
