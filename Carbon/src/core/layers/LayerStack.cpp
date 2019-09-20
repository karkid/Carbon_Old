#include "capch.h"
#include "LayerStack.h"

namespace Carbon
{
    LayerStack::LayerStack()
    {
    }

    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_LayerBook)
        {
            if (layer)
            {
                delete layer;
            }
        }
    }

    void LayerStack::pushLayer(Layer* layer)
    {
        m_LayerBook.emplace(m_LayerBook.begin() + m_LayerIterator, layer);
        m_LayerIterator++;
    }

    void LayerStack::pushOverLay(Layer* overLay)
    {
        m_LayerBook.emplace_back(overLay);
    }

    void LayerStack::popLayer(Layer* layer)
    {
        auto it = std::find(m_LayerBook.begin(), m_LayerBook.end(), layer);
        if (it != m_LayerBook.end())
        {
            m_LayerBook.erase(it);
            layer->onDetach();
            m_LayerIterator--;
        }
    }

    void LayerStack::popOverLay(Layer* overLay)
    {
        auto it = std::find(m_LayerBook.begin(), m_LayerBook.end(), overLay);
        if (it != m_LayerBook.end())
        {
            m_LayerBook.erase(it);
        };
    }

    std::vector<Layer *>::iterator LayerStack::begin()
    {
        return m_LayerBook.begin();
    }

    std::vector<Layer *>::iterator LayerStack::end()
    {
        return m_LayerBook.end();
    }
}
