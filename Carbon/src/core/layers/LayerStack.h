#pragma once

#include "core/core.h"
#include "Layer.h"

namespace Carbon
{
    class CARBON_API LayerStack
    {
    public:
        LayerStack();
        virtual ~LayerStack();

        void pushLayer(Layer* layer);
        void pushOverLay(Layer* overLay);

        void popLayer(Layer* layer);
        void popOverLay(Layer* overLay);

        std::vector<Layer*>::iterator begin();
        std::vector<Layer*>::iterator end();
    private:
        std::vector<Layer*> m_LayerBook;
        unsigned int m_LayerIterator = 0;
    };
}