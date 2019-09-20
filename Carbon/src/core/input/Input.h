#pragma once

#include "core/core.h"

namespace Carbon
{
    struct CARBON_API Point
    {
        union
        {
            double data[2];
            struct
            {
                double x;
                double y;
            };
        };
    };

    class CARBON_API Input
    {
    public:
        inline static bool isKeyPressed(int keycode) { return s_Instance->isKeyPressedImpl(keycode); }
        inline static bool isMouseButtonPressed(int button) { return s_Instance->isMouseButtonPressedImpl(button); }
        inline static Point getMousePosition() { return s_Instance->getMousePositionImpl(); }
    protected:
        inline virtual bool isKeyPressedImpl(int keycode) = 0;
        inline virtual bool isMouseButtonPressedImpl(int button) = 0;
        inline virtual Point getMousePositionImpl() = 0;
    private:
        static Input* s_Instance;
    };
}
