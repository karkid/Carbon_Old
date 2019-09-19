#include "capch.h"

#include "GLFWWindow.h"
#include "core/events/WindowEvent.h"
#include "core/events/KeyEvent.h"
#include "core/events/MouseEvent.h"
#include "GLFW/glfw3.h"

namespace Carbon
{
    Window* Window::Create(const WindowProps& props)
    {
        return new GLFWWindow(props);
    }

    static bool s_GLFWInitialized = false;
    static void glfw_error_callback(int error, const char* description)
    {
        LOG_ERROR("Glfw Error %d: %s\n", error, description);
    }

    GLFWWindow::GLFWWindow(const WindowProps & props)
    {
        init(props);
    }

    GLFWWindow::~GLFWWindow()
    {
        shutDown();
    }

    void GLFWWindow::onUpdate()
    {
        glfwPollEvents();
    }

    unsigned int GLFWWindow::width() const
    {
        return m_Data.width;
    }

    unsigned int GLFWWindow::height() const
    {
        return m_Data.height;
    }

    void GLFWWindow::setEventCallback(const EventCallBackFn & callbackFn)
    {
        m_Data.eventCallBack = callbackFn;
    }

    void GLFWWindow::setVSync(bool enabled)
    {
        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }
        m_Data.bVSyc = enabled;
    }

    bool GLFWWindow::isVSync() const
    {
        return m_Data.bVSyc;
    }

    void * GLFWWindow::nativeWindow()
    {
        return m_Window;
    }

    void GLFWWindow::clearWindow()
    {

    }

    void GLFWWindow::init(const WindowProps & props)
    {
        m_Data.title = props.title;
        m_Data.width = props.width;
        m_Data.height = props.height;

        if (!s_GLFWInitialized)
        {
            int bSucess = glfwInit();
            ASSERT(bSucess, "Failed to initialized GLFW");
            if (bSucess)
            {
                s_GLFWInitialized = true;
            }
        }

        m_Window = glfwCreateWindow((int)m_Data.width, (int)m_Data.height, m_Data.title.c_str(), nullptr, nullptr);

        // m_Data will be get on event call back
        glfwSetWindowUserPointer(m_Window, &m_Data);
        setVSync(true);

        //Window Events
        glfwSetWindowCloseCallback(m_Window, &GLFWWindow::onWindowClose);
        glfwSetWindowFocusCallback(m_Window, &GLFWWindow::onWindowFocus);
        glfwSetWindowSizeCallback(m_Window, &GLFWWindow::onWindowSize);
        glfwSetKeyCallback(m_Window, &GLFWWindow::onKey);
        glfwSetMouseButtonCallback(m_Window, &GLFWWindow::onMouseButton);
        glfwSetScrollCallback(m_Window, &GLFWWindow::onScroll);
        glfwSetErrorCallback(glfw_error_callback);
    }

    void GLFWWindow::shutDown()
    {
        glfwDestroyWindow(m_Window);
    }

    void GLFWWindow::onWindowClose(GLFWwindow * window)
    {
        WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent ev;
        data.eventCallBack(ev);
    }

    void GLFWWindow::onWindowFocus(GLFWwindow * window, int focusIn)
    {
        WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
        if (focusIn)
        {
            WindowFocuseEvent ev;
            data.eventCallBack(ev);
        }
        else
        {
            WindowBlurEvent ev;
            data.eventCallBack(ev);
        };
    }

    void GLFWWindow::onWindowSize(GLFWwindow * window, int width, int height)
    {
        WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent ev(width, height);
        data.eventCallBack(ev);
    }

    void GLFWWindow::onKey(GLFWwindow * window, int key, int scancode, int action, int mods)
    {
        WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
        static unsigned int cntRepeat = 1;
        switch (action) 
        {
            case GLFW_PRESS:
            {
                cntRepeat = 1;
                KeyPressedEvent ev(key, cntRepeat);
                data.eventCallBack(ev);
            }
            break;
            case GLFW_RELEASE:
            {
                cntRepeat = 0;
                KeyReleasedEvent ev(key);
                data.eventCallBack(ev);
            }
            break;
            case GLFW_REPEAT:
            {
                cntRepeat++;
                KeyPressedEvent ev(key, cntRepeat);
                data.eventCallBack(ev);
            }
            break;
            default:
                break;
        };
    }

    void GLFWWindow::onMouseButton(GLFWwindow * window, int button, int action, int mods)
    {
        WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action) 
        {
            case GLFW_PRESS:
            {
                MouseDownEvent ev(button);
                data.eventCallBack(ev);
            }
            break;
            case GLFW_RELEASE:
            {
                MouseUpEvent ev(button);
                data.eventCallBack(ev);
            }
            break;
            default:
                break;
        };
    }

    void GLFWWindow::onScroll(GLFWwindow * window, double xOffset, double yOffset)
    {
        WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseWheelEvent ev(xOffset, yOffset);
        data.eventCallBack(ev);
    }
}