#include "Carbon.h"

class SandboxApp : public Carbon::Application
{
public:
    SandboxApp(){}
    ~SandboxApp() {}
};

Carbon::Application* Carbon::CreateApplication() {
    return new SandboxApp();
}