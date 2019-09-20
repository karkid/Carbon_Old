#include "capch.h"

#include "GLFWWindowInput.h"
#include "core/Application.h"
#include "GLFW/glfw3.h"

namespace Carbon
{
    Input* Input::s_Instance = new GLFWWindowInput();

    inline bool GLFWWindowInput::isKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().nativeWindow());
        int status = glfwGetKey(window, keycode);
        return status == GLFW_PRESS || status == GLFW_REPEAT;
    }
    inline bool GLFWWindowInput::isMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().nativeWindow());
        int status = glfwGetMouseButton(window, button);
        return status == GLFW_PRESS;
    }
    inline Point GLFWWindowInput::getMousePositionImpl()
    {
        Point mousePt;
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().nativeWindow());
        glfwGetCursorPos(window, &mousePt.x, &mousePt.y);
        return mousePt;
    }
}