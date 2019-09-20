#pragma once

#include "core/input/Input.h"

namespace Carbon
{
    class GLFWWindowInput : public Input
    {
    public:
        inline bool isKeyPressedImpl(int keycode) override;
        inline bool isMouseButtonPressedImpl(int button) override;
        inline Point getMousePositionImpl() override;
    };
}